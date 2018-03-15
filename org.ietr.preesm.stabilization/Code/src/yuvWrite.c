/**
* Write YUV file
*
* @file yuvWrite.c
* @author kdesnos
* @date 2016.09.06
* @version 1.0
* @copyright CECILL-C
*/

#include <stdio.h>
#include <stdlib.h>

#include "yuvWrite.h"


static FILE *ptfile;

void initYUVWrite(){
	
	// Open the file in write binary mode
	if ((ptfile = fopen(PATH_WRITE, "wb")) == NULL)
	{
		fprintf(stderr, "ERROR: Task read cannot open output yuv_file '%s'\n", PATH_WRITE);
#ifdef _WIN32
		system("PAUSE");
#endif
		exit(0);
	}
}

void yuvWrite(const int width, const int height, const unsigned char * const y, const unsigned char * const u, const unsigned char * const v){
	// write into the file
	fwrite(y, sizeof(char), width * height, ptfile);
	fwrite(u, sizeof(char), width * height / 4, ptfile);
	fwrite(v, sizeof(char), width * height / 4, ptfile);

	// make sure the content is written every time
	// (slower, but safer since the application may be stopped at any time)
	fflush(ptfile);
}


void endYUVWrite(){
	fclose(ptfile);
}