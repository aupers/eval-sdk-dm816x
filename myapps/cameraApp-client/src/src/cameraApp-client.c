/* Example libgstcam application

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
#include <stdlib.h>
#include <glib.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "libgstcam.h"

/****************************************************************
 * Constants
 ****************************************************************/
#define PROGNAME "cameraApp-client"

#define MAX_STR 255

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
static int bus = 0;             /* 0: system, 1: session */

cameraHandler camera;
GMainLoop *loop;

static struct input_event in_event;
static struct pollfd fds[1];

static pthread_t loop_thread_t;

enum mode {
    START,
    STOP,
    SNAPSHOT,
    STARTV,
    STOPV,
    EVENT
};

static enum mode mode = START;
static const char *filename;

/****************************************************************
 * process_error
 ****************************************************************/
inline void process_error(int err, char *error_string)
{
    if (err) {
        printf("%s\n", error_string);
        exit(255);
    }
}

/****************************************************************
 * Usage
 ****************************************************************/
static void show_usage(char *progname)
{
    fprintf(stderr, "\n%s [-h] [-d <debug lvl>] [-S] < -s | -p | -c | -v | -V | -w gpio > \n\n", progname);

    fprintf(stderr,
            "             -s                   starts the camera\n");
    fprintf(stderr,
            "             -p                   stops the camera\n");
    fprintf(stderr,
            "             -c                   takes an jpeg snapshot\n");
    fprintf(stderr,
            "             -v                   starts recording a video\n");
    fprintf(stderr,
            "             -V                   stops the video recording\n");
    fprintf(stderr,
            "             -w /dev/input/eventX waits for the EVKEY event to trigger camera capture\n");
    fprintf(stderr,
            "             -h                   print usage information\n");
    fprintf(stderr,
            "             -d <debug level>     set debug level 0-2\n");
    fprintf(stderr,
            "             -S                   use session bus instead of system bus\n");
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

    while ((opt = getopt(argc, argv, "spcvVw:hd:S")) != -1) {
        switch (opt) {
        case 's':
            mode = START;
            break;
                
        case 'p':
            mode = STOP;
            break;
        
        case 'c':
            mode = SNAPSHOT;
            break;
                
        case 'v':
            mode = STARTV;
            break;
                
        case 'V':
            mode = STOPV;
            break;

        case 'w':
            mode = EVENT;
            filename = optarg;
            break;
                
        case 'h':
            show_usage(progname);
            exit(0);
            break;

        case 'd':
            debug_level = atoi(optarg);
            vdbg("Program debug level set to %d", debug_level);
            ret = camera_set_debug_level(debug_level);
            process_error(ret, "can't set gstcam Library debug level");
            break;

        case 'S':
            bus = 1;
            vdbg("D-Bus bus set to session");
            break;

        default:               /* '?' */
            show_usage(progname);
            printf("ERROR: Unknown option '%c'\n", opt);
            exit(-1);
        }
    }

    if (optind < argc) {
        show_usage(progname);
        printf("ERROR: unexpected command line parameter: %s\n",
               argv[optind]);
        exit(-1);
    }
}

/***************************************************************************
 * event_type
 ***************************************************************************/
enum _event_type {
    EVSYN,
    EVKEY
} event_type;

struct input_event {                                                                                                    
    struct timeval time;                                                                                            
    unsigned short type;                                                                                            
    unsigned short code;                                                                                            
    unsigned int value;                                                                                             
};


/***************************************************************************
 * input_event
 ***************************************************************************/
void *input_event(void *parm)
{
    int i;
    /* */
    if (poll(fds, 2, -1) <= 0) {
        fprintf(stderr, "Error while doing poll of events");
        return (void *)-1;
    }
    for (i = 0; i <= sizeof(fds) / sizeof(struct pollfd); i++) {
        if (fds[i].revents == POLLIN) {
            if (read(fds[i].fd, &in_event, sizeof(in_event)) <
                sizeof(in_event)) {
                fprintf(stderr, "Error reading event from %d", fds[i].fd);
                return (void *)-1;
            }
            if (in_event.type == EVKEY) {
                /* Button down */
                if (in_event.value == 1) {
                    printf("Button is down!\n");
                    camera_snapshot(camera);
                } else {
                    printf("Button is up!\n");
                }
            }
        }
    }
    
    return NULL;
}

/****************************************************************
 * main
 ****************************************************************/
int main(int argc, char *argv[])
{

    parse_options(argc, argv);
    int ret;

    /* We have our own main loop */
    vdbg("Initializing library");
    ret = cameraClient_init(0);
    process_error(ret, "can't connect to cameraClient");

    loop = g_main_loop_new(NULL, TRUE);

    camera = camera_connect();
    if (!camera) {
        fprintf(stderr, "\nFailed to connect to the camera daemon\n");
        return -1;
    }
    
    switch (mode) {
        case START:
            vdbg("Starting camera");
            if (camera_is_running(camera)){
                printf("Camera is already running\n");
                exit(255);
            }

            /* Set properties of image capture, video recording and viewfinder */
#if 1
            vdbg("Setting view finder");
            //ret = camera_set_view_finder_pipe(camera, "queue ! TIDmaiVideoSink videoOutput=component videoStd=720p_60");
            ret = camera_set_view_finder_pipe(camera, "queue ! TIDmaiVideoSink videoOutput=composite sync=false");
            process_error(ret, "can't set view finder");
#endif
            vdbg("Setting video src");		
            //ret = camera_set_video_src_pipe(camera, "v4l2src always-copy=false chain-ipipe=false ! dmaiaccel ! capsfilter caps=video/x-raw-yuv,format=(fourcc)NV12,width=1280,height=720,framerate=(fraction)23/1 ");
            ret = camera_set_video_src_pipe(camera, "v4l2src always-copy=FALSE input-src=composite ! dmaiaccel ! capsfilter caps=video/x-raw-yuv,format=(fourcc)NV12,width=720,height=480,pitch=736,framerate=(fraction)30000/1001");
            process_error(ret, "can't set video src");
            
            vdbg("Setting snapshot pipe ");
            ret = camera_set_snapshot_pipe(camera, "queue ! dmaienc_jpeg ! jifmux ! multifilesink async=false location=snapshot_%d.jpg");
            process_error(ret, "can't set snapshot pipe");

            vdbg("Setting video record pipe ");
            ret = camera_set_video_recording_pipe(camera, "queue ! dmaienc_h264 encodingpreset=2 ratecontrol=2 targetbitrate=1500000 ! qtmux name=mux ! filesink location=/tmp/video.mov");
            process_error(ret, "can't set video pipe");
            
            vdbg("Setting audio src ");
            ret = camera_set_audio_src_pipe(camera, "alsasrc ! capsfilter caps=audio/x-raw-int,rate=(int)44100,channels=(int)2");
            process_error(ret, "can't set audio src pipe");
            
            vdbg("Setting audio record pipe ");
            ret = camera_set_audio_recording_pipe(camera, "queue ! dmaienc_aac bitrate=64000");
            process_error(ret, "can't set audio recording pipe");
            
            ret = camera_start(camera);
            process_error(ret, "Failed to start camera");
            break;
        case STOP:
            vdbg("Stoping camera");
            if (!camera_is_running(camera)){
                printf("Camera is not running\n");
                exit(255);
            }
            ret = camera_stop(camera);
            process_error(ret, "Failed to stop camera");
            break;
        case SNAPSHOT:
            if (!camera_is_running(camera)){
                printf("Camera is not running\n");
                exit(255);
            }
            ret = camera_snapshot(camera);
            process_error(ret, "Failed to take snapshot");
            printf("Snapshot taken\n");
            break;
        case STARTV:
            if (!camera_is_running(camera)){
                printf("Camera is not running\n");
                exit(255);
            }            
            ret = camera_start_video_recording(camera);
            process_error(ret, "Failed to start video recording");
            printf("Video recording started\n");
            break;
        case STOPV:
            if (!camera_is_running(camera)){
                printf("Camera is not running\n");
                exit(255);
            }            
            ret = camera_stop_video_recording(camera);
            process_error(ret, "Failed to stop video recording");
            printf("Video recording stoped\n");
            break;
        case EVENT:
            fds[0].fd = open(filename, O_RDONLY);
            fds[0].events = POLLIN;
            fds[0].revents = 0;
            
            in_event.type = 0;
            in_event.value = 0;
            pthread_create(&loop_thread_t, NULL, input_event, NULL);

            g_main_loop_run(loop);            
            break;

        default:
            printf("Unkown operation mode");
            exit(255);
            break;
    }
    
    return 0;
}
