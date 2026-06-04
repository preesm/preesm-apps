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

int counter = 0;
char videoFiles[NB_VIDEO][200] =
        {
        PATH_VIDEO_FOLDER "akiyo_cif.yuv",
        PATH_VIDEO_FOLDER "city_cif.yuv",
        PATH_VIDEO_FOLDER "coastguard_cif.yuv",
        PATH_VIDEO_FOLDER "container_cif.yuv",
        PATH_VIDEO_FOLDER "crew_cif.yuv",
        PATH_VIDEO_FOLDER "foreman_cif.yuv",
        PATH_VIDEO_FOLDER "hall_monitor_cif.yuv",
        PATH_VIDEO_FOLDER "harbour_cif.yuv",
        PATH_VIDEO_FOLDER "mobile_cif.yuv",
        PATH_VIDEO_FOLDER "mother_daughter_cif.yuv",
        PATH_VIDEO_FOLDER "news_cif.yuv",
        PATH_VIDEO_FOLDER "pamphlet_cif.yuv",
        PATH_VIDEO_FOLDER "silent_cif.yuv"
        };
/*========================================================================

   initReadYUV DEFINITION

   ======================================================================*/
void initReadYUV(int width, int height) {
    int fsize;
#if 0
    if((ptfile = fopen(PATH_VIDEO, "rb")) == NULL )
    {
        fprintf(stderr,"ERROR: Task read cannot open yuv_file '%s'\n", PATH_VIDEO);
#ifdef _WIN32
        system("PAUSE");
#endif
        exit(0);
    }

#ifdef PREESM_VERBOSE
    printf("Opened file '%s'\n", PATH_VIDEO);
#endif
#else
    if (counter >= NB_VIDEO)
        exit(0);

    if((ptfile = fopen(videoFiles[counter], "rb")) == NULL )
    {
        fprintf(stderr,"ERROR: Task read cannot open yuv_file '%s'\n", videoFiles[counter]);
        exit(0);
    }
    printf("Opened file '%s'\n", videoFiles[counter]);
    counter++;
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

#ifdef PREESM_VERBOSE
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
    fprintf(stderr, "\nMain: %d frames in %d us - %f fps\n", FPS_INTERVAL, time, (1000000*FPS_INTERVAL) / (float)time);
    startTiming(0);
  }
  int res = fread(y, sizeof(char), width * height, ptfile);
  res += fread(u, sizeof(char), width * height / 4, ptfile);
  res += fread(v, sizeof(char), width * height / 4, ptfile);
  if (res == 0) {
    printf("Error while read file\n");
    exit(1);
  }
}

void readYUV_float(int width, int height, float *y, float *u, float *v) {

    if (ftell(ptfile) / (width*height + width*height / 2) >= NB_FRAME){
        rewind(ptfile);
    }

    if (ftell(ptfile) / (width*height + width*height / 2) % FPS_INTERVAL == 0) {
        unsigned int time = 0;
        time = stopTiming(0);
        fprintf(stderr, "\nMain: %d frames in %d us - %f fps\n", FPS_INTERVAL, time, (1000000*FPS_INTERVAL) / (float)time);
        startTiming(0);
    }

    unsigned int res = 0;

//    int res = fread(y, sizeof(char), width * height, ptfile);
    for (int i = 0; i < width * height; i++){
        unsigned char temp;
        res += fread(&temp, sizeof(char), width * height, ptfile);
        y[i] = (float) temp;
    }

//    res += fread(u, sizeof(char), width * height / 4, ptfile);
    for (int i = 0; i < width * height / 4; i++){
        unsigned char temp;
        res += fread(&temp, sizeof(char), width * height / 4, ptfile);
        u[i] = (float) temp;
    }

//    res += fread(v, sizeof(char), width * height / 4, ptfile);
    for (int i = 0; i < width * height / 4; i++){
        unsigned char temp;
        res += fread(&temp, sizeof(char), width * height / 4, ptfile);
        v[i] = (float) temp;
    }

    if (res == 0) {
        printf("Error while read file\n");
        exit(1);
    }
}

void endYUVRead(){
	fclose(ptfile);
}
