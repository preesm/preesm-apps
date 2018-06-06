/*
	============================================================================
	Name        : readYUV.c
	Author      : kdesnos
    Author      : mpelcat
	Version     : 1.1
	Copyright   : CECILL-C
	Description :
	============================================================================
*/


#include "yuvRead.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clock.h"

#include <stdio.h>
#include <unistd.h>

#include <libv4l2.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/videodev2.h>

#define _GNU_SOURCE
#include <sys/mman.h>

#define FPS_INTERVAL 10

/*========================================================================

   Global Variable

   ======================================================================*/
static FILE *ptfile ;

/*========================================================================

   initReadYUV DEFINITION

   ======================================================================*/
void initReadYUV_old(int width, int height) {
    int fsize;
    if((ptfile = fopen(PATH_VIDEO, "rb")) == NULL )
    {
        fprintf(stderr,"ERROR: Task read cannot open yuv_file '%s'\n", PATH_VIDEO);
#ifdef _WIN32
        system("PAUSE");
#endif
        exit(0);
    }

#ifdef VERBOSE
    printf("Opened file '%s'\n", PATH_VIDEO);
#endif

    // Obtain file size:
    fseek (ptfile , 0 , SEEK_END);
    fsize = ftell (ptfile);
    rewind (ptfile);
    if(fsize < NB_FRAME*(width*height + width*height/2))
    {
        fprintf(stderr,"ERROR: Task read yuv_file incorrect size");
#ifdef _WIN32
        system("PAUSE");
#endif
        return;
    }

#ifdef VERBOSE
    printf("Correct size for yuv_file '%s'\n", PATH_VIDEO);
#endif

    // Set initial clock
    startTiming(0);
}


int videoCamFd;
struct v4l2_buffer bufferinfo;

void initReadYUV(int width, int height) {
    if((videoCamFd = open("/dev/video0", O_RDWR)) < 0){
        perror("open");
        exit(1);
    }

    struct v4l2_capability cap;
    if(ioctl(videoCamFd, VIDIOC_QUERYCAP, &cap) < 0){
        perror("VIDIOC_QUERYCAP");
        exit(1);
    }

    struct v4l2_format format;
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    format.fmt.pix.width = 640;
    format.fmt.pix.height = 480;

    if(ioctl(videoCamFd, VIDIOC_S_FMT, &format) < 0){
        perror("VIDIOC_S_FMT");
        exit(1);
    }

    struct v4l2_requestbuffers bufrequest;
    bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufrequest.memory = V4L2_MEMORY_MMAP;
    bufrequest.count = 1;

    if(ioctl(videoCamFd, VIDIOC_REQBUFS, &bufrequest) < 0){
        perror("VIDIOC_REQBUFS");
        exit(1);
    }


    memset(&bufferinfo, 0, sizeof(bufferinfo));
    bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufferinfo.memory = V4L2_MEMORY_MMAP;
    bufferinfo.index = 0; /* Queueing buffer index 0. */

    // Put the buffer in the incoming queue.
    if(ioctl(videoCamFd, VIDIOC_QBUF, &bufferinfo) < 0){
        perror("VIDIOC_QBUF");
        exit(1);
    }

    // Activate streaming
    int type = bufferinfo.type;
    if(ioctl(videoCamFd, VIDIOC_STREAMON, &type) < 0){
        perror("VIDIOC_STREAMON");
        exit(1);
    }

	// Dequeue the buffer.
	if(ioctl(videoCamFd, VIDIOC_DQBUF, &bufferinfo) < 0){
		perror("VIDIOC_QBUF");
		exit(1);
	}

	bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	bufferinfo.memory = V4L2_MEMORY_MMAP;
	/* Set the index if using several buffers */

	// Queue the next one.
	if(ioctl(videoCamFd, VIDIOC_QBUF, &bufferinfo) < 0){
		perror("VIDIOC_QBUF");
		exit(1);
	}


    // Set initial clock
    startTiming(0);

}
/*========================================================================

   readYUV DEFINITION

   ======================================================================*/
void readYUV(int width, int height, unsigned char *y, unsigned char *u, unsigned char *v) {

	void* buffer_start = mmap(
	    NULL,
	    bufferinfo.length,
	    PROT_READ | PROT_WRITE,
	    MAP_SHARED,
		videoCamFd,
	    bufferinfo.m.offset
	);

	if(buffer_start == MAP_FAILED){
	    perror("mmap");
	    exit(1);
	}

	memset(buffer_start, 0, bufferinfo.length);


}
void readYUV_old(int width, int height, unsigned char *y, unsigned char *u, unsigned char *v) {

	if (ftell(ptfile) / (width*height + width*height / 2) >= NB_FRAME){
		rewind(ptfile);
	}

	if (ftell(ptfile) / (width*height + width*height / 2) % FPS_INTERVAL == 0) {
		unsigned int time = 0;
        time = stopTiming(0);
		printf("\nMain: %d frames in %d us - %f fps\n", FPS_INTERVAL - 1, time, (FPS_INTERVAL - 1.0) / (float)time * 1000000);
        startTiming(0);
    }
    fread(y, sizeof(char), width * height, ptfile);
    fread(u, sizeof(char), width * height / 4, ptfile);
    fread(v, sizeof(char), width * height / 4, ptfile);
}

void endYUVRead(){
	fclose(ptfile);
}
