/*
	============================================================================
	Name        : readYUV.h
	Author      : kdesnos & mpelcat
	Version     : 1.1
	Copyright   : CECILL-C
	Description : Actor code to read a file from the hard drive
	============================================================================
*/

#ifndef READ_YUV_H
#define READ_YUV_H

#include "preesm.h"

#ifndef VIDEO_ID
#define VIDEO_ID 1
#endif

//#define VIDEO_NAME "akiyo_cif"
//#define VIDEO_NAME "city_cif"
//#define VIDEO_NAME "coastguard_cif"
//#define VIDEO_NAME "container_cif"
//#define VIDEO_NAME "crew_cif"
//#define VIDEO_NAME "foreman_cif"
//#define VIDEO_NAME "hall_monitor_cif"
//#define VIDEO_NAME "harbour_cif"
//#define VIDEO_NAME "mobile_cif"
//#define VIDEO_NAME "mother_daughter_cif"
//#define VIDEO_NAME "news_cif"
//#define VIDEO_NAME "pamphlet_cif"
//#define VIDEO_NAME "silent_cif"

    #if VIDEO_ID == 0
    #define VIDEO_NAME "akiyo_cif"
    #elif VIDEO_ID == 1
    #define VIDEO_NAME "city_cif"
    #elif VIDEO_ID == 2
    #define VIDEO_NAME "coastguard_cif"
    #elif VIDEO_ID == 3
    #define VIDEO_NAME "container_cif"
    #elif VIDEO_ID == 4
    #define VIDEO_NAME "crew_cif"
    #elif VIDEO_ID == 5
    #define VIDEO_NAME "foreman_cif"
    #elif VIDEO_ID == 6
    #define VIDEO_NAME "hall_monitor_cif"
    #elif VIDEO_ID == 7
    #define VIDEO_NAME "harbour_cif"
    #elif VIDEO_ID == 8
    #define VIDEO_NAME "mobile_cif"
    #elif VIDEO_ID == 9
    #define VIDEO_NAME "mother_daughter_cif"
    #elif VIDEO_ID == 10
    #define VIDEO_NAME "news_cif"
    #elif VIDEO_ID == 11
    #define VIDEO_NAME "pamphlet_cif"
    #elif VIDEO_ID == 12
    #define VIDEO_NAME "silent_cif"
    #endif

#define VIDEO_FILE VIDEO_NAME ".yuv"
//#define PATH_VIDEO PROJECT_ROOT_PATH "/dat/" VIDEO_FILE
#define PATH_VIDEO "./" VIDEO_FILE

#define NB_VIDEO    13
//#define PATH_VIDEO_FOLDER PROJECT_ROOT_PATH "/dat/"
#define PATH_VIDEO_FOLDER "./"

#define PSNR_FILE_EXT "_psnr.txt"
#define PSNR_FILE VIDEO_NAME "_psnr.txt"

#define NB_FRAME 300

/**
* Initialize the readYUV actor.
* Open the YUV file at the given PATH and check its size.
*
* @param width
*        The width of the opened YUV file
* @param height
*        The heigth of the opened YUV file
*/
void initReadYUV(int width, int height);

/**
* Read a new frame from the YUV file.
*
* @param width
*        The width of the opened YUV file
* @param height
*        The heigth of the opened YUV file
* param y
*       Destination of the Y component read from the file
* param u
*       Destination of the U component read from the file
* param v
*       Destination of the V component read from the file
*/
void readYUV(int width, int height, OUT unsigned char *y, OUT unsigned char *u, OUT unsigned char *v);

void readYUV_float(int width, int height, OUT float *y, OUT float *u, OUT float *v);

#endif
