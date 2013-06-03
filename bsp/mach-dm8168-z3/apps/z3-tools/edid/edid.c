/******************************************************************************
** Copyright (c) 2011 Z3 Technology, LLC.  All rights reserved.  This file, 
** including all design, code and information therein ("file"), is exclusively
** owned and controlled by Z3 Technology, LLC ("Z3") and may only be used by 
** Z3's licensee in conjunction with Z3 devices or technologies.  Use with 
** non-Z3 devices or technologies is expressly prohibited.  This file is 
** included among the "Licensed Materials" in the licensee's license agreement
** with Z3 and is subject to all terms therein.  All derivative works are also
** the exclusive property of Z3 and subject to all the terms herein and all
** the terms of the license agreement with Z3.  Z3 is providing this file
** "as is" solely for Z3's licensee's use in developing programs and solutions
** for Z3 devices.  Z3 makes no representation or warranty that the file is
** non-infringing of the rights of third parties and expressly disclaims any
** warranty with respect to the adequacy of the implementation, including but
** not limited to any warranties of merchantability or warranty of fitness for
** a particular purpose.
**
** This copyright notice, restricted rights legend and other proprietary
** rights markings must be reproduced without modification in any copies of
** any part of this work and in any derivative work.  Removal or modification
** of any part of this notice is prohibited.
*******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <getopt.h>

#define EDID_BASE_BLOCK_SIZE 128
#define EDID_EXTENSION_BLOCK_SIZE 128
#define EDID_DETAILED_TIMING_SIZE 18

#define EDID_SUPPORT_AC3

struct edid_detailed_timing_description {
	unsigned char pixel_clock[2];
	unsigned char horizontal_size[3];
	unsigned char vertical_size[3];
	unsigned char blank[4];

	unsigned char image_size[3];
	unsigned char border[2];
	unsigned char flags;

};

struct edid {
	unsigned char header[8];
	unsigned char manf_id[2];
	unsigned char product_id[2];
	unsigned char serial_num[4];

	/* offset 0x10 */
	unsigned char manf_date[2];
	unsigned char edid_version[2];
	unsigned char video_input;
	unsigned char horiz_cm;
	unsigned char vert_cm;
	unsigned char gamma;

	/* offset 0x18 */
	unsigned char feature_support;
	unsigned char chromaticity[10];

	unsigned char established_timings[2];
	unsigned char manf_timings;

	unsigned char standard_timings[8][2];

	unsigned char detailed_timings[4][EDID_DETAILED_TIMING_SIZE];

	unsigned char extension_flag;
	unsigned char checksum;
} edid;

static unsigned char cea_861_extension_block[EDID_EXTENSION_BLOCK_SIZE];

unsigned char detailed_1080i_cea_format_5[EDID_DETAILED_TIMING_SIZE] = {
	0x01, 0x1d, 0x80, 0x18, 0x71, 0x1c, 0x16, 0x20,
	0x58, 0x2c, 0x25, 0x00, 0x0f, 0x48, 0x42, 0x00,
	0x00, 0x9e
};

unsigned char detailed_720p_cea_format_4[EDID_DETAILED_TIMING_SIZE] = {
	0x01, 0x1d, 0x00, 0x72, 0x51, 0xd0, 0x1e, 0x20,
	0x6e, 0x28, 0x55, 0x00, 0x0f, 0x48, 0x42, 0x00,
	0x00, 0x1e
};

unsigned char detailed_480p_cea_format_3[EDID_DETAILED_TIMING_SIZE] = {
	0x8e, 0x0a, 0xd0, 0x8a, 0x20, 0xe0, 0x2d, 0x10,
	0x10, 0x3e, 0x96, 0x00, 0x1f, 0x09, 0x00, 0x00,
	0x00, 0x18
};

unsigned char detailed_monitor_id[EDID_DETAILED_TIMING_SIZE] = {
	0x00, 0x00, 0x00, 0xfc, 0x00, 'Z', '3', 'T',
	' ', 'D', 'M', '3', '6', '8', 'A', '0',
	'1', '\n'
};

unsigned char display_limits[EDID_DETAILED_TIMING_SIZE] = {
	0x00, 0x00, 0x00, 0xFD, 
	0x00, //flags
	0x14, 0x4B, // Vertical refresh min/max in Hz
	0x0F, 0x46, // Horizontal rate min/max in kHz
	0x0c,       // Max pixel clock in MHz/10
	0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
};

unsigned char chromaticity_example2[10] = {
	0xee, 0x91, 0xa3, 0x54, 0x4c, 0x99, 0x26, 0x0f,
	0x50, 0x54,
};

unsigned int eeprom_addr=0x50;

void
usage(const char *progname)
{
	fprintf( stderr, "Usage: %s [--i2cbus=<0|1|2>] [--i2caddr=0x<hex 7-bit address>] [--monitorid=<name>]\n\n", progname ) ;
}

int main(int argc, char *argv[])
{
	int i;
	int ret;
	char command_buf[128];
	unsigned char *cea_ptr;
	unsigned char checksum;
	unsigned int i2c_bus = 0;

	int c, index;
	const char shortOptions[] = "i:m:h";
    const struct option longOptions[] = {
        {"help",             no_argument,       NULL, 'h'},
        {"i2cbus",           required_argument, NULL, 'i'},
        {"i2caddr",          required_argument, NULL, 'a'},
        {"monitorid",        required_argument, NULL, 'm'},
        {0, 0, 0, 0}
    };
	unsigned char *monitor_start, *monitor_end, *monitor_tmp, *newname;

    for (;;) {
        c = getopt_long(argc, argv, shortOptions, longOptions, &index);

        if (c == -1) {
            break;
        }

        switch (c) {
		case 0:
			break;

		case 'h':
			usage(argv[0]);
			exit(0);
			break;

		case 'm':
			monitor_start = &detailed_monitor_id[5];
			monitor_end   = &detailed_monitor_id[EDID_DETAILED_TIMING_SIZE];
			newname = (unsigned char *)optarg;

			if ( newname != NULL ) {
				for ( monitor_tmp = monitor_start;
					  monitor_tmp < monitor_end && *newname != '\0';
					  monitor_tmp++, newname++ ) {
					*monitor_tmp = *newname;
				}
				memset( monitor_tmp, ' ', monitor_end-monitor_tmp );
			}
			break;

		case 'i':
			i2c_bus = atoi(optarg);
			break;

		case 'a':
			eeprom_addr = (int) strtoul(optarg, NULL, 0);
			break;

		default:
			usage(argv[0]);
			exit(1);
        }
	}

	if ( optind < argc ) {

		usage(argv[0]);
		exit(1);
	}

	/* EDID based on example 2 in Appendix A of VESA Enhanced EDID Standard rev 2 */

	memset( &edid, '\0', sizeof(edid) );

	edid.header[0] = 0x00;
	edid.header[1] = 0xff;
	edid.header[2] = 0xff;
	edid.header[3] = 0xff;
	edid.header[4] = 0xff;
	edid.header[5] = 0xff;
	edid.header[6] = 0xff;
	edid.header[7] = 0x00;

	edid.manf_id[0] = 0x6a; //ZTT in compressed ASCII
	edid.manf_id[1] = 0x94;

	edid.product_id[0] = 0x80; // LSB
	edid.product_id[1] = 0x36; // MSB

	edid.serial_num[0] = 0x00;
	edid.serial_num[1] = 0x00;
	edid.serial_num[2] = 0x00;
	edid.serial_num[3] = 0x00;

	edid.manf_date[0] = 0xff;
	edid.manf_date[1] = 0x14; // 2010 model year

	edid.edid_version[0] = 1;
	edid.edid_version[1] = 3;

	edid.video_input = 0x80; // Digital, HDMI-a, 8 bit color

	edid.horiz_cm = 0xa0;
	edid.vert_cm  = 0x5a;

	edid.gamma = 0x78;  // Gamma = 2.20: register is (Gamma*100)-100

/*
 	Power Management and Supported Feature(s):
7 	standby
6 	suspend
5 	active-off/low power

4 	Display type:

     00=monochrome, 01=RGB colour, 10=non RGB multicolour, 11=undefined
3

2 	standard colour space
1 	preferred timing mode
0 	default GTF supported
*/
	edid.feature_support = 0x0a;  
	memcpy( edid.chromaticity,
			chromaticity_example2,
			sizeof( edid.chromaticity ) );

	edid.established_timings[0] = 0x25; // 640x480 @60Hz, 640x480@75Hz, 800x600@60Hz
	edid.established_timings[1] = 0x4e; // 800x600@75Hz, 1024x768@60Hz, 1024x768@70Hz, 1024x768@75Hz
	edid.manf_timings = 0;

	// Standard timing format:
	// byte 0: (Horizontal addressable pixels ÷ 8)- 31
    // byte 1: bits 7-6: 00=16:10, 01=4:3, 10=5:4, 11=16:9
    //       : bits 5-0: (Field refresh rate in Hz)-60

	memset( edid.standard_timings, 1, sizeof(edid.standard_timings) );

	edid.standard_timings[0][0] = 0x81; // 1280x1024@60fps
	edid.standard_timings[0][1] = 0x80;


	memcpy( &edid.detailed_timings[0][0],
			detailed_720p_cea_format_4,
			EDID_DETAILED_TIMING_SIZE );

	memcpy( &edid.detailed_timings[1][0],
			detailed_480p_cea_format_3,
			EDID_DETAILED_TIMING_SIZE );

	memcpy( &edid.detailed_timings[2][0],
			detailed_monitor_id,
			EDID_DETAILED_TIMING_SIZE );

	memcpy( &edid.detailed_timings[3][0],
			display_limits,
			EDID_DETAILED_TIMING_SIZE );


	// 1 EDID extension block
	edid.extension_flag = 1;

	
	edid.checksum = 0;
	for (i=0; i<EDID_BASE_BLOCK_SIZE-1; i++ ) {
		edid.checksum += ((unsigned char *)&edid)[i];
	}
	edid.checksum = (unsigned char) (0 - edid.checksum);

	for ( i=0; i<EDID_BASE_BLOCK_SIZE; i++ ) {
		sprintf( command_buf, "/usr/local/sbin/i2cset -y -n %u 0x%x 0x%x 0x%x\n",
				 i2c_bus,
				 eeprom_addr,
				 i,
				 (unsigned int) ((unsigned char *)&edid)[i] );
//		fprintf( stderr, "%s", command_buf );
		ret = system( command_buf );
		if ( ret < 0 || !( WIFEXITED(ret) && (WEXITSTATUS(ret)== 0) )) {
			fprintf( stderr, "i2c write failed !!!\n" );
			return 1;
		}
	}


	/* CEA Extension block */
	memset( cea_861_extension_block, '\0', sizeof(cea_861_extension_block) );
	cea_ptr = &cea_861_extension_block[0];


	*cea_ptr++ = 0x02; // Block-tag code 2
	*cea_ptr++ = 0x03; // version 3
	*cea_ptr++ = 0x00; //  Detailed Timing descriptors start offset (fixed up later)
	*cea_ptr++ = 0x76; // no underscan, base audio, YCbCr 4:2:2 and 4:4:4, 6 native formats

	*cea_ptr++ = 0x4f; // Video Data block code, 15 bytes
	*cea_ptr++ = 0x05; // 1080i-30 format
	*cea_ptr++ = 0x14; // 1080i-25 format
	*cea_ptr++ = 0x04; // 720p-60 format
	*cea_ptr++ = 0x13; // 720p-50 format
#if defined(Z3_HDMI_RX_FULLHD)
	*cea_ptr++ = 0x10; // 1080p-60
	*cea_ptr++ = 0x1f; // 1080p-50
#else
	*cea_ptr++ = 0x21; // 1080p-25
	*cea_ptr++ = 0x22; // 1080p-30
#endif
	*cea_ptr++ = 0x20; // 1080p-24
	*cea_ptr++ = 0x03; // 480p 16:9 format
	*cea_ptr++ = 0x02; // 480p 4:3  format
	*cea_ptr++ = 0x12; // 576p 16:9 format
	*cea_ptr++ = 0x11; // 576p 4:3  format
	*cea_ptr++ = 0x07; // 480i 16:9 format
	*cea_ptr++ = 0x06; // 480i 4:3 format
	*cea_ptr++ = 0x16; // 480i 16:9 format
	*cea_ptr++ = 0x15; // 480i 4:3 format

 	*cea_ptr++ = 0x26; // Audio Data block code, 3 bytes
	*cea_ptr++ = 0x09; // LPCM 2 channels
	*cea_ptr++ = 0x07; // Supported sampling frequencies: 48kHz, 44.1kHz, 32kHz
	*cea_ptr++ = 0x01; // Support sample word sizes: 16 bits
#if defined(EDID_SUPPORT_AC3)
	*cea_ptr++ = 0x15; // AC-3 6 channels
	*cea_ptr++ = 0x07; // Supported sampling frequencies: 48kHz, 44.1kHz, 32kHz
	*cea_ptr++ = 0x60; // Max bitrate in units of 8kbps

	*cea_ptr++ = 0x83; // Speaker allocation block tag, 3 bytes
	*cea_ptr++ = 0x0f; // Front-left and front-right, LFE, Front Center, and Rear Left
	*cea_ptr++ = 0x00; // reserved
	*cea_ptr++ = 0x00; // reserved
#else
	*cea_ptr++ = 0x83; // Speaker allocation block tag, 3 bytes
	*cea_ptr++ = 0x01; // Front-left and front-right
	*cea_ptr++ = 0x00; // reserved
	*cea_ptr++ = 0x00; // reserved
#endif
	*cea_ptr++ = 0x65; // Vendor-specific data
	*cea_ptr++ = 0x03; // HDMI vendor OUI
	*cea_ptr++ = 0x0C;
	*cea_ptr++ = 0x00;
	*cea_ptr++ = 0x10; // components of Source Physical Address
	*cea_ptr++ = 0x00;

	// Fix-up DTD offset 
	cea_861_extension_block[2] = (cea_ptr-&cea_861_extension_block[0]);

	if (cea_ptr < &cea_861_extension_block[EDID_EXTENSION_BLOCK_SIZE-(EDID_DETAILED_TIMING_SIZE+1)] )  {
		memcpy( &cea_ptr,
				detailed_1080i_cea_format_5,
				EDID_DETAILED_TIMING_SIZE );
		cea_ptr += EDID_DETAILED_TIMING_SIZE;
	}

	if (cea_ptr < &cea_861_extension_block[EDID_EXTENSION_BLOCK_SIZE-(EDID_DETAILED_TIMING_SIZE+1)] )  {
		memcpy( cea_ptr,
				detailed_720p_cea_format_4,
				EDID_DETAILED_TIMING_SIZE );
		cea_ptr += EDID_DETAILED_TIMING_SIZE;
	}
	
	if (cea_ptr < &cea_861_extension_block[EDID_EXTENSION_BLOCK_SIZE-(EDID_DETAILED_TIMING_SIZE+1)] )  {
		memcpy( cea_ptr,
				detailed_480p_cea_format_3,
				EDID_DETAILED_TIMING_SIZE );
		cea_ptr += EDID_DETAILED_TIMING_SIZE;
	}

	checksum = 0;
	for (i=0; i<EDID_EXTENSION_BLOCK_SIZE-1; i++ ) {
		checksum += cea_861_extension_block[i];
	}
	cea_861_extension_block[EDID_EXTENSION_BLOCK_SIZE-1] = (unsigned char)(0-checksum);


#if 0
	{
		unsigned char canned_extension[EDID_EXTENSION_BLOCK_SIZE] = {
			0x02, 0x03, 0x20, 0x70, 0x49, 0x10, 0x04, 0x05, 0x03, 0x02, 0x07, 0x06, 0x20, 0x01, 0x26, 0x09,
			0x07, 0x07, 0x15, 0x07, 0x50, 0x83, 0x01, 0x00, 0x00, 0x66, 0x03, 0x0c, 0x00, 0x10, 0x00, 0x80,

			0x01, 0x1d, 0x80, 0x18, 0x71, 0x1c, 0x16, 0x20, 0x58, 0x2c, 0x25, 0x00, 0x40, 0x84, 0x63, 0x00,
			0x00, 0x9e, 0x8c, 0x0a, 0xd0, 0x8a, 0x20, 0xe0, 0x2d, 0x10, 0x10, 0x3e, 0x96, 0x00, 0x40, 0x84,
			0x63, 0x00, 0x00, 0x18, 0x8c, 0x0a, 0xd0, 0x8a, 0x20, 0xe0, 0x2d, 0x10, 0x10, 0x3e, 0x96, 0x00,
			0xb0, 0x84, 0x43, 0x00, 0x00, 0x18, 0x8c, 0x0a, 0xa0, 0x14, 0x51, 0xf0, 0x16, 0x00, 0x26, 0x7c,
			0x43, 0x00, 0xb0, 0x84, 0x43, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
		};

		memcpy( cea_861_extension_block, canned_extension, EDID_EXTENSION_BLOCK_SIZE );
	}
#endif

	for ( i=0; i<EDID_EXTENSION_BLOCK_SIZE; i++ ) {
		sprintf( command_buf, "/usr/local/sbin/i2cset -y %u 0x%x 0x%x 0x%x\n",
				 i2c_bus,
				 eeprom_addr,
				 i+EDID_BASE_BLOCK_SIZE,
				 (unsigned int) cea_861_extension_block[i] );
//		fprintf( stderr, "%s", command_buf );
		ret = system( command_buf );
		if ( ret < 0 || !( WIFEXITED(ret) && (WEXITSTATUS(ret)== 0) )) {
			fprintf( stderr, "i2c write failed !!!\n" );
			return 1;
		}
	}

	fprintf( stderr, "EDID programmed successfully.\n" );
	return 0;
}
