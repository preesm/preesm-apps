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

/*========================================================================

 Global Variable

 ======================================================================*/
static FILE *ptfile;

/*========================================================================

 initReadYUV DEFINITION

 ======================================================================*/
void initReadYUV(int width, int height) {
	int fsize;
	if ((ptfile = fopen(PATH, "rb")) == NULL) {
		fprintf(stderr,"ERROR: Task read cannot open yuv_file '%s'\n", PATH);
		system("PAUSE");
		return;
	}

#ifdef VERBOSE
	printf("Opened file '%s'\n", PATH);
#endif

	// Obtain file size:
	fseek(ptfile, 0, SEEK_END);
	fsize = ftell(ptfile);
	rewind(ptfile);
	if (fsize < NB_FRAME * (width * height + width * height / 2)) {
		fprintf(stderr, "ERROR: Task read yuv_file incorrect size");
		system("PAUSE");
		return;
	}

#ifdef VERBOSE
	printf("Correct size for yuv_file '%s'\n", PATH);
#endif

	// Set initial clock
	startTiming(0);
}

/*========================================================================

 readY DEFINITION

 ======================================================================*/
void readY(int width, int height, unsigned char *y, unsigned char *u,
		unsigned char *v) {
	int i;
	static int uvInitialized = 0;

	if (ftell(ptfile) / (width * height + width * height / 2) >= NB_FRAME) {
		unsigned int time = 0;
		rewind(ptfile);
		time = stopTiming(0);
		printf("\nMain: %d frames in %d us - %f fps\n", NB_FRAME - 1, time,
				(NB_FRAME - 1.0) / (float) time * 1000000);
		startTiming(0);
	}

	fread(y, sizeof(char), width * height, ptfile);

	// u and v values are ignored since the output is in black and white
	fseek(ptfile, width * height / 2, SEEK_CUR);

	if (uvInitialized == 0) {
		for (i = 0; i < width * height / 4; i++) {
			// Both black and white have u and v equal to 128 in YUV representation
			u[i] = 128;
			v[i] = 128;
		}
		uvInitialized++;
	}
}
