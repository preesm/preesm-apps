


#include "v4l2uvc.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
#include <libv4l2.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/videodev2.h>
*/

#define clamp(x) (x>255)? 255 : ((x<0)? 0 : x);


#define UINT8 char
#define UINT32 int

void cam(UINT8* r, UINT8* g, UINT8* b, int width, int height, int id);

int main() {

	char imgR[640*480*4];
	char imgG[640*480*4];
	char imgB[640*480*4];

	cam(imgR, imgG, imgB, 640, 480,0);



	printf("OK\n");
}


void yuyv_to_rgb (struct vdIn *vd, unsigned char* r, unsigned char* g, unsigned char* b){
	int i;
	unsigned char *ptrIn = vd->framebuffer;

	for (i = 0;  i < vd->height*vd->width;  i+=2){
	    int c = ptrIn[0] - 16;
	    int d = ptrIn[1] - 128;
	    int e = ptrIn[3] - 128;

	    r[i] = clamp(( 298 * c + 409 * e + 128) >> 8); // red
	    g[i] = clamp(( 298 * c - 100 * d - 208 * e + 128) >> 8); // green
	    b[i] = clamp(( 298 * c + 516 * d + 128) >> 8); // blue

	    c = ptrIn[2] - 16;
	    r[i+1] = clamp(( 298 * c + 409 * e + 128) >> 8); // red
	    g[i+1] = clamp(( 298 * c - 100 * d - 208 * e + 128) >> 8); // green
	    b[i+1] = clamp(( 298 * c + 516 * d + 128) >> 8); // blue

	    ptrIn += 4;
	}
}

void cam(UINT8* r, UINT8* g, UINT8* b, int width, int height, int id){


	static struct vdIn *videoIn = NULL;


	printf("cam %d %d %d\n", width, height, id);

	/* Fct Call */
	if(id == 0){
		if(videoIn == NULL){
			videoIn = (struct vdIn *) calloc (1, sizeof (struct vdIn));
			init_videoIn(videoIn, "/dev/video0", width, height, V4L2_PIX_FMT_YUYV, 1);
		}

	    if (uvcGrab (videoIn) < 0) {
			fprintf (stderr, "Error grabbing\n");
			close_v4l2 (videoIn);
			exit (1);
		}

	    yuyv_to_rgb(videoIn, r,g,b);

	}else{
		if(videoIn == NULL){
			videoIn = (struct vdIn *) calloc (1, sizeof (struct vdIn));
			init_videoIn(videoIn, "/dev/video0", width, height, V4L2_PIX_FMT_YUYV, 1);
		}

	    if (uvcGrab (videoIn) < 0) {
			fprintf (stderr, "Error grabbing\n");
			close_v4l2 (videoIn);
			exit (1);
		}
	    yuyv_to_rgb(videoIn, r,g,b);
	}
}
