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

#define FPS_INTERVAL 10

/*========================================================================

   Global Variable

   ======================================================================*/
static FILE *ptfile ;

/*========================================================================

   initReadYUV DEFINITION

   ======================================================================*/
void initReadYUV(int width, int height) {
    int fsize;
    if((ptfile = fopen(PATH_VIDEO, "rb")) == NULL )
    {
        fprintf(stderr,"ERROR: Task read cannot open yuv_file '%s'\n", PATH_VIDEO);
        system("PAUSE");
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
        system("PAUSE");
        return;
    }

#ifdef VERBOSE
    printf("Correct size for yuv_file '%s'\n", PATH_VIDEO);
#endif

    // Set initial clock
    startTiming(0);
}

/*========================================================================

   readYUV DEFINITION

   ======================================================================*/
void readYUV(int width, int height, unsigned char *y, unsigned char *u, unsigned char *v) {

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
