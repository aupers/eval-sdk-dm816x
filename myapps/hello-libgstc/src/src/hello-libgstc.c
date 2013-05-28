/* Example libgstc application

 * Copyright 2011 RidgeRun. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY RIDGERUN ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL RIDGERUN OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of RidgeRun.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include "libgstc.h"

/****************************************************************
 * Constants
 ****************************************************************/
#define PROGNAME "hello-libgstc"

#define MAX_STR 1024

#ifdef __arm__
#define TEST_PIPELINE "filesrc name=src ! qtdemux ! queue ! dmaidec_aac ! alsasink"
#else
#define TEST_PIPELINE "filesrc name=src ! aacparse ! ffdec_aac ! autoaudiosink"
#endif

const char *INSTRUCTIONS = "Controls:\n  0 = destroy all pipelines\n  1 = play\n  2 = pause \n  3 = increase speed\n  4 = decrease speed\n  5 = normal speed\n  6 = get duration\n  7 = get position\n  8 = inject eos\n  9 = set pipeline state to null\n  q = quit\n\n";

/***************************************************************************
 * Debug Macros
 ***************************************************************************/
#ifdef DEBUG_INCLUDE_TIMESTAMP
# define dbg_time() do {                                                \
                struct timeval time;                                    \
                int rc;                                                 \
                rc=gettimeofday(&time, NULL);                           \
                if(rc==0) {                                             \
                        printf("%lu.%06lu: ", time.tv_sec, time.tv_usec); \
                }                                                       \
        } while (0)
#else
# define dbg_time() do {} while (0)
#endif

# define  prt(format, arg...) do { dbg_time() ; printf(PROGNAME " %s: " format "\n", __FUNCTION__, ##arg); } while (0);

# define  dbg(format, arg...) if (debug_level > 0) \
                do { dbg_time() ; printf(PROGNAME " %s: " format "\n", __FUNCTION__, ##arg); } while (0);

# define vdbg(format, arg...) if (debug_level > 1) \
                do { dbg_time() ; printf(PROGNAME " %s: " format "\n", __FUNCTION__, ##arg); } while (0);

/************************************************************************
 * Private Data
 ************************************************************************/

static char *progname = NULL;

/* values that can be set from the command line */
static int debug_level = 0;
static int bus = 0; /* 0: system, 1: session */
static int run_test_suite = 0;
static int run_video_record = 0;
static char pipeline[MAX_STR];
static pthread_cond_t eos_cond  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t eos_mutex = PTHREAD_MUTEX_INITIALIZER;

/****************************************************************
 * process_error
 ****************************************************************/
inline void process_error(int err, char *error_string)
{
	if (err) {
		printf("%s\n", error_string);
		printf("Destroying all pipelines\n");
		libgstc_pipeline_destroy_all();
		exit(255);
	}
}

/****************************************************************
 * waitForEoS
 *
 * timeout in seconds
 ****************************************************************/
void waitForEoS(int timeout)
{
	int ret;
	struct timespec   ts;
	struct timeval    tp;

	dbg("Waiting %d seconds for sink element to reach end of stream", timeout);

	ret = pthread_mutex_lock(&eos_mutex);
	process_error(ret, "ERROR - can't lock EOS mutex");

	ret =  gettimeofday(&tp, NULL);
	process_error(ret, "ERROR - can't get time of day");

	/* Convert from timeval to timespec */
	ts.tv_sec  = tp.tv_sec;
	ts.tv_nsec = tp.tv_usec * 1000;
	ts.tv_sec += timeout;

	ret = pthread_cond_timedwait(&eos_cond, &eos_mutex, &ts);

	if (ret == ETIMEDOUT) {
		printf("ERROR: never received EOS signal after waiting %d seconds\n", timeout);
		goto out;
	}

	process_error(ret, "ERROR - wait for EOS failed");

out:
	ret = pthread_mutex_unlock(&eos_mutex);
	process_error(ret, "ERROR - can't lock EOS mutex");
}

/****************************************************************
 * injectEoS
 ****************************************************************/
void injectEoS(pipelineHandle handle, int timeout)
{
	int ret;

	dbg("Sending EOS to source element");
	ret = libgstc_pipeline_send_eos(handle);
	process_error(ret, "ERROR - can't inject eos into pipeline");

	waitForEoS(timeout);
}

/****************************************************************
 * onEoS
 *
 * This function runs on a different thread (glib mail loop)
 * than the rest of the application
 *
 ****************************************************************/
void onEoS(pipelineHandle handle)
{
	int ret;
	dbg("Sink element reached end of stream");

	ret = pthread_mutex_lock(&eos_mutex);
	process_error(ret, "ERROR - can't lock EOS mutex");

	ret = pthread_cond_signal(&eos_cond);
	process_error(ret, "ERROR - can't signal EOS condition");

	ret = pthread_mutex_unlock(&eos_mutex);
	process_error(ret, "ERROR - can't lock EOS mutex");
}

/****************************************************************
 * onStateChanged
 ****************************************************************/
void onStateChanged(pipelineHandle handle, int old_state, int new_state, char* src)
{
	dbg("New state (%s): ", src);
	switch (new_state) {
	case LIBGSTC_EVENT_PLAYING:
		dbg("GST_STATE_PLAYING");
	        break;
	case LIBGSTC_EVENT_PAUSED:
		dbg("GST_STATE_PAUSED");
		break;
	case LIBGSTC_EVENT_READY:
		dbg("GST_STATE_READY");
		break;
	case LIBGSTC_EVENT_NULL:
		dbg("GST_STATE_NULL");
		break;
	default:
		printf("Error: Unknown GStreamer state\n");
	}
}

/****************************************************************
 * test_sleep
 ****************************************************************/
void inline test_sleep(int t)
{
	vdbg("sleeping %d sec", t);
	sleep(t);
}

/****************************************************************
 * video_recording_libgstc
 *
 * The user must supply a recording pipeline where the sink
 * element has the name "sink"
 *
 * huser pipeline must be in the GST_STATE_NULL state on entry
 *
 ****************************************************************/
void video_recording_glibc(pipelineHandle huser)
{
	const char *default_filename = "av-glibc-test-000.mpg";
	char filename[22];
	char digits[4];
	int ret;
	int i;

	strncpy(filename, default_filename, 22);
	for (i = 1; i < 1000; i++) {
		sprintf(digits, "%3.3d", i);
		memcpy(&filename[14], digits, 3);
		ret = libgstc_set_property_string(huser, "sink", "location", filename);
		process_error(ret, "ERROR - can't set sink filename");

		ret = libgstc_pipeline_play(huser);
		process_error(ret, "ERROR - can't set pipeline to play");

		test_sleep(10);

		injectEoS(huser, 5);

		ret = libgstc_pipeline_null(huser);
		process_error(ret, "ERROR - can't set pipeline state to null");
	}
}

/****************************************************************
 * test_libgstc
 *
 * The user must supply a pipeline that supports trick play
 * (e.g. skip, seek, speed changes)
 ****************************************************************/
void test_glibc(pipelineHandle huser)
{
	int ret;
	const char * p1="audiotestsrc name=src ! fakesink name=sink";
	pipelineHandle h1;
	const char * p2="videotestsrc name=src ! fakesink name=sink";
	pipelineHandle h2;
	const char * p3="filesrc location=/dev/zero name=src ! fakesink name=sink";
	pipelineHandle h3;
	char val8;
	int val32;
	int64_t val64;
	char str128[128];
	char *valstr128 = &str128[0];

	ret = libgstc_pipeline_create(p1, &h1);
	process_error(ret, "T01: ERROR - can't create p1 pipeline");

	ret = libgstc_pipeline_create(p2, &h2);
	process_error(ret, "T02: ERROR - can't create p2 pipeline");

	ret = libgstc_pipeline_destroy(h1);
	process_error(ret, "T03: ERROR - can't destroy p1 pipeline");

	ret = libgstc_pipeline_create(p1, &h1);
	process_error(ret, "T04: ERROR - can't create p1 pipeline");

	ret = libgstc_pipeline_set_state_event_callback(h1, onStateChanged);
	process_error(ret, "T05: ERROR - can't register callback handle on p1");

	ret = libgstc_pipeline_set_state_event_callback(h2, onStateChanged);
	process_error(ret, "T06: ERROR - can't register callback handle on p2");

	ret = libgstc_pipeline_set_eos_event_callback(h1, onEoS);
	process_error(ret, "T07: ERROR - can't register eos handle on p1");

	ret = libgstc_pipeline_set_eos_event_callback(h2, onEoS);
	process_error(ret, "T08: ERROR - can't register eos handle on p2");

	ret = libgstc_pipeline_play(h1);
	process_error(ret, "T09: ERROR - can't set p1 state to play");
	test_sleep(1);

	ret = libgstc_pipeline_play(h2);
	process_error(ret, "T10: ERROR - can't set p2 state to play");
	test_sleep(1);

	ret = libgstc_pipeline_pause(h2);
	process_error(ret, "T11: ERROR - can't set p2 state to pause");
	test_sleep(1);

	ret = libgstc_pipeline_ready(h1);
	process_error(ret, "T12: ERROR - can't set p1 state to ready");


	ret = libgstc_get_property_boolean(h1, "src", "do-timestamp", &val8);
	process_error(ret, "T13: ERROR - can't get boolean property value from p1 audiotestsrc");

	ret = libgstc_set_property_boolean(h1, "src", "do-timestamp", 1);
	process_error(ret, "T14: ERROR - can't set boolean property value from p1 audiotestsrc");

	ret = libgstc_get_property_boolean(h1, "src", "do-timestamp", &val8);
	process_error(ret, "T15: ERROR - can't get bool property value from p1 audiotestsrc");
	process_error(!val8, "T16: ERROR - bool value that was set wasn't returned when fetched p1 audiotestsrc");


	ret = libgstc_get_property_int32(h1, "src", "num-buffers", &val32);
	process_error(ret, "T17: ERROR - can't get int32 property value from p1 audiotestsrc");

	ret = libgstc_set_property_int32(h1, "src", "num-buffers", 500);
	process_error(ret, "T18: ERROR - can't set int32 property value from p1 audiotestsrc");

	ret = libgstc_get_property_int32(h1, "src", "num-buffers", &val32);
	process_error(ret, "T19: ERROR - can't get int32 property value from p1 audiotestsrc");
	process_error(val32 !=500, "T12: ERROR - int32 value that was set wasn't returned when fetched p1 audiotestsrc");


	ret = libgstc_get_property_int64(h1, "src", "timestamp-offset", &val64);
	process_error(ret, "T20: ERROR - can't get int64 property value from p1 audiotestsrc");

	ret = libgstc_set_property_int64(h1, "src", "timestamp-offset", 92233720368547758LL);
	process_error(ret, "T21: ERROR - can't set int64 property value from p1 audiotestsrc");

	ret = libgstc_get_property_int64(h1, "src", "timestamp-offset", &val64);
	process_error(ret, "T22: ERROR - can't get int64 property value from p1 audiotestsrc");
	process_error(val64 != 92233720368547758LL, "T12: ERROR - int64 value that was set wasn't returned when fetched p1 audiotestsrc");

	/* Need an element with read / write string parameter, so using location parameter in filesrc */
	ret = libgstc_pipeline_create(p3, &h3);
	process_error(ret, "T23: ERROR - can't create p3 pipeline");

	ret = libgstc_pipeline_set_state_event_callback(h3, onStateChanged);
	process_error(ret, "T24: ERROR - can't register callback handle on p3");

	ret = libgstc_pipeline_set_eos_event_callback(h3, onEoS);
	process_error(ret, "T25: ERROR - can't register eos handle on p3");

	ret = libgstc_get_property_string(h3, "src", "location", &valstr128, 128);
	process_error(ret, "T26: ERROR - can't get string property value from p3 filesrc");
	process_error(strcmp("/dev/zero", valstr128), "T12: ERROR - fetched string value different than preset value, p3 filesrc");

	ret = libgstc_set_property_string(h3, "src", "location", "/dev/null");
	process_error(ret, "T27: ERROR - can't set string property value on p3 filesrc");

	ret = libgstc_get_property_string(h3, "src", "location", &valstr128, 128);
	process_error(ret, "T28: ERROR - can't get string property value from p3 filesrc");
	process_error(strcmp("/dev/null", valstr128), "T12: ERROR - fetched string value different than set value, p3 filesrc");


	ret = libgstc_pipeline_null(h2);
	process_error(ret, "T29: ERROR - can't set p2 state to null");

	ret = libgstc_pipeline_play(h1);
	process_error(ret, "T30: ERROR - can't set p1 state to play");
	test_sleep(1);

	ret = libgstc_pipeline_play(h2);
	process_error(ret, "T31: ERROR - can't set p2 state to play");
	test_sleep(1);

	ret = libgstc_pipeline_play(huser);
	process_error(ret, "T32: ERROR - can't set supplied pipeline state  to play");
	test_sleep(1);

	ret = libgstc_get_pipeline_position(huser, &val64);
	process_error(ret, "T33: ERROR - can't get current pipeline position on p1");

	ret = libgstc_get_media_duration(huser, &val64);
	process_error(ret, "T34: ERROR - can't get current pipeline duration on user supplied pipeline");

	ret = libgstc_set_pipeline_speed(huser, 0.5);
	process_error(ret, "T35: ERROR - can't set speed to 0.5 on user supplied pipeline");

	ret = libgstc_media_skip(huser, 2000L);
	process_error(ret, "T36: ERROR - can't skip ahead in user supplied pipeline");
	test_sleep(1);

	ret = libgstc_media_seek(huser, 2000L);
	process_error(ret, "T37: ERROR - can't seek backwards in user supplied pipeline");
	test_sleep(1);

	injectEoS(huser, 5);

	ret = libgstc_pipeline_destroy_all();
	process_error(ret, "T39: ERROR - can't destroy all pipelines");
	test_sleep(1);

	printf("Test suite passed\n");

	exit(0);
}

/****************************************************************
 * process_user_input
 ****************************************************************/
void process_user_input(pipelineHandle handle)
{
	int running = 1;
	char comm;
	double speed = 1.0;
	int ret;
	int64_t duration;
	int64_t position;

	printf("%s", INSTRUCTIONS);

	vdbg("Loop processing user input");
	while(running) {
		ret = scanf ("%c", &comm);

		if (ret != 1) {
			printf("Error: unable to get user input\n");
			exit(255);
		}

		if (iscntrl(comm) || (comm == ' ') || (comm == '\t')) {
			continue;
		}

		switch(comm) {
		case '0':
			vdbg("Destroy all pipelines");
			ret = libgstc_pipeline_destroy_all();
			process_error(ret, "can't destroy all pipelines");
			break;
		case '1':
			vdbg("Play");
			ret = libgstc_pipeline_play(handle);
			process_error(ret, "can't change state to play\n    check your pipeline");
			break;
		case '2':
			vdbg("Pause");
			ret = libgstc_pipeline_pause(handle);
			process_error(ret, "can't change state to pause");
			break;
		case '3':
			vdbg("Increase speed");
			speed += 0.5;
			if (speed > 8.0) {
				speed = 8.0;
			}
			ret = libgstc_set_pipeline_speed(handle, speed);
			process_error(ret, "Can't increase speed");
			break;
		case '4':
			vdbg("Decrease speed");
			speed -= 0.1;
			if (speed <= 0.0) {
				speed = 0.1;
			}
			ret = libgstc_set_pipeline_speed(handle, speed);
			process_error(ret, "Can't decrease speed");
			break;
		case '5':
			vdbg("Normal speed");
			speed = 1.0;
			ret = libgstc_set_pipeline_speed(handle, speed);
			process_error(ret, "Can't set speed to normal");
			break;
		case '6':
			vdbg("Get duration");
			
			ret = libgstc_get_media_duration(handle, &duration);
			process_error(ret, "Can't get media duration");
			duration /= 1000000;
			printf ("The duration on the pipeline is %u:%02u:%02u.%03u (%lld milliseconds)\n",
						   (int)(duration / (1000 * 60 * 60)),
						   (int)((duration / (1000 * 60)) % 60),
						   (int)((duration / 1000) % 60),
						   (int)(duration % 1000), 
						   duration);
			break;
		case '7':
			vdbg("Get Position");
			
			ret = libgstc_get_pipeline_position(handle, &position);
			process_error(ret, "Can't get media position");
			position /= 1000000;
			printf ("The position on the pipeline is %u:%02u:%02u.%03u (%lld milliseconds)\n",
						   (int)(position / (1000 * 60 * 60)),
						   (int)((position / (1000 * 60)) % 60),
						   (int)((position / 1000) % 60),
						   (int)(position % 1000), 
						   position);
			break;
		case '8':
			vdbg("Inject EoS");
			injectEoS(handle, 5);
			break;
		case '9':
			vdbg("Null");
			ret = libgstc_pipeline_null(handle);
			process_error(ret, "can't change state to null");
			break;
		case 'q':
			vdbg("Quit");
			running = 0;
			break;
		default:
			printf("Command not recognized: %c\n%s", comm, INSTRUCTIONS);
		}	
	}
}
/****************************************************************
 * Usage
 ****************************************************************/
static void show_usage(char *progname)
{
        fprintf(stderr, "\n%s [-h] [-d <debug lvl>] [-r] [-s] [-t] <GStreamer pipeline>\n", progname);
        fprintf(stderr, "   -h                     print usage information\n");
        fprintf(stderr, "   -d <debug level>       set debug level 0-2\n");
        fprintf(stderr, "   -r                     run the libgstc video record test forever. <GStreamer pipeline> must support\n");
        fprintf(stderr, "                          filesink element named sink.  Each recording is 10 seconds long.\n");
        fprintf(stderr, "   -s                     use session bus instead of system bus\n");
        fprintf(stderr, "   -t                     run the libgstc test suite and exit. <GStreamer pipeline> must support trick play\n");
        fprintf(stderr, "   <GStreamer pipeline>   pipeline to control\n");
        fprintf(stderr, " \n");
        fprintf(stderr, "Desktop examples: \n");
        fprintf(stderr, "   a) Verbose debug using the session bus to play an MP3 file using FFMPEG\n");
	fprintf(stderr, "      %s -d 2 -s \"filesrc location=/opt/media/TurnLeft.mp3 ! mp3parse ! ffdec_mp3 ! autoaudiosink\"\n",
		progname);
	fprintf(stderr, "   b) Use session bus to play an MP3 file using mad\n");
	fprintf(stderr, "      %s -s \"filesrc location=/opt/media/TurnLeft.mp3 ! mad ! autoaudiosink\"\n",
		progname);
	fprintf(stderr, "   c) Run test suite with a pipeline that supports trickplay\n");
	fprintf(stderr, "      %s -s -t \"filesrc location=/opt/media/bbb.mp3 ! mp3parse ! ffdec_mp3 ! autoaudiosink\"\n",
		progname);
	fprintf(stderr, "   d) Run video record test suite for up to 100 loops\n");
	fprintf(stderr, "      %s -d 2 -s -r \"v4l2src ! ffenc_mpeg2video ! mpegpsmux ! filesink name=sink\"\n",
		progname);
	fprintf(stderr, "\nEmbedded examples: \n");
	fprintf(stderr, "   a) Verbose debug using the session bus to play an MP3 file using FFMPEG\n");
	fprintf(stderr, "      %s -d 2 -s \"filesrc location=/opt/media/davincieffect.aac ! qtdemux ! queue ! dmaidec_aac ! alsasink\"\n",
		progname);
	fprintf(stderr, "   b) Run video record test suite for up to 100 loops\n");
	fprintf(stderr, "      %s -d 2 -r \"alsasrc latency-time=30000 buffer-time=800000 ! audio/x-raw-int, rate=(int)22050 ! dmaienc_mp3 bitrate=128000 outputBufferSize=131072 ! queue ! mpegpsmux name=m v4l2src always-copy=false input-src=composite ! video/x-raw-yuv,format=(fourcc)NV12,width=720,height=480,pitch=736 ! dmaiaccel ! dmaienc_mpeg2 encodingpreset=2 targetbitrate=3600000 ! dmaiperf print-arm-load=true ! queue ! m. m. ! filesink name=sink\"\n",
		progname);
        fprintf(stderr, "\n\n");
}

/***************************************************************************
 * parse_options
 ***************************************************************************/
static void parse_options(int argc, char *argv[])
{
        int opt;
	int ret;

        /* for show_usage */
        progname = argv[0];

        while ((opt = getopt(argc, argv, "hd:rst")) != -1) {
                switch (opt) {
                case 'h' :
                        show_usage(progname);
			exit(0);
                        break;

                case 'd' :
                        debug_level = atoi(optarg);
                        vdbg("Program debug level set to %d", debug_level);
			ret = libgstc_set_debug_level(debug_level);
			process_error(ret, "can't set GStreamer daemon client library debug level");
                        break;

		case 'r' :
                        run_video_record = 1;
                        vdbg("Run video record test for up to 100 loops");
                        break;

                case 's' :
                        bus = 1;
                        vdbg("D-Bus bus set to session");
                        break;

		case 't' :
                        run_test_suite = 1;
                        vdbg("Run test suite and exit");
                        break;

                default: /* '?' */
                        show_usage(progname);
                        printf("ERROR: Unknown option '%c'\n", opt);
                        exit(-1);
                }
        }

	if (optind < argc) {
		strncpy(pipeline, argv[optind], MAX_STR);
		pipeline[MAX_STR-1] ='\0';
		optind++;
	} else {
		show_usage(progname);
		printf("ERROR: Missing argument: <GStreamer pipeline>\n");
		exit(-1);
	}

	if (optind < argc) {
		show_usage(progname);
		printf("ERROR: unexpected command line parameter: %s\n", argv[optind]);
		exit(-1);
	}
}

/****************************************************************
 * main
 ****************************************************************/
int main(int argc, char** argv)
{
	pipelineHandle handle;
	int ret;

	parse_options(argc, argv);

	vdbg("Initialize GStreamer client library");
	ret = libgstc_init(bus, 1);
	process_error(ret, "can't initialize GStreamer client library");

	/* Check if daemon is running */
	if( libgstc_ping() != 0) {
		printf("GStreamer daemon not running\n");
		if (bus) {
			printf("   gstd --session &\n");
		} else {
			printf("   gstd &\n");
		}
		exit(255);
	}
		
	dbg("Creating pipeline: %s", pipeline);
	ret = libgstc_pipeline_create(pipeline, &handle);
	process_error(ret, "can't create pipeline");
	
	ret = libgstc_pipeline_set_state_event_callback(handle, onStateChanged);
	process_error(ret, "can't register callback handle");

	ret = libgstc_pipeline_set_eos_event_callback(handle, onEoS);
	process_error(ret, "can't register eos handle");

	if (run_video_record) {
		vdbg("Video record sequentially");
		video_recording_glibc(handle);
	}

	if (run_test_suite) {
		vdbg("Test suite");
		test_glibc(handle);
	}

	process_user_input(handle);

	dbg("Closing all pipelines");
	libgstc_fini();
	
	return 0;
}
