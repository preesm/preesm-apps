/*
	============================================================================
	Name        : readYUV.c
	Author      : kdesnos
    Author      : mpelcat
	Version     : 1.0
	Copyright   : CECILL-C
	Description :
	============================================================================
*/

#include "yuvRead.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*========================================================================

   Global Variable

   ======================================================================*/
static FILE *ptYuvFile = NULL ;
static unsigned int setNbFrames = 0;

/*========================================================================

   initReadYUV DEFINITION

   ======================================================================*/
int initReadYUV(char* filePath, int xSize, int ySize, int nbFrames) {
    int fsize;
    if((ptYuvFile = fopen(filePath, "rb")) == NULL )
    {
        fprintf(stderr,"ERROR: Task read cannot open yuv_file '%s'\n", filePath);
        return FAILURE;
    }

#ifdef VERBOSE
    printf("Opened file '%s'\n", filePath);
#endif

    // Obtain file size:
    fseek (ptYuvFile , 0 , SEEK_END);
    fsize = ftell (ptYuvFile);
    rewind (ptYuvFile);
    if(fsize < nbFrames*(xSize*ySize + xSize*ySize/2))
    {
        fprintf(stderr,"ERROR: Task read yuv_file incorrect size");
        return FAILURE;
    }

#ifdef VERBOSE
    printf("Correct size for yuv_file '%s'\n", filePath);
#endif

    setNbFrames = nbFrames;

    return SUCCESS;
}

/*========================================================================

   readYUV DEFINITION

   ======================================================================*/
void readYUV(unsigned int xSize, unsigned int ySize, unsigned char *y, unsigned char *u, unsigned char *v) {
	size_t read; 
#ifdef VERBOSE
    printf("Reading xsize %d ysize %d\n", xSize, ySize);
#endif
	// Writing circularly if we go further than input file size
    if( ftell(ptYuvFile)/(xSize*ySize + xSize*ySize/2) >= setNbFrames){
        rewind(ptYuvFile);
    }
	
    read = fread(y, sizeof(char), xSize * ySize, ptYuvFile);
    if (read != (xSize * ySize)) {
		printf("EOF or Error\n");
	}
    read = fread(u, sizeof(char), xSize * ySize / 4, ptYuvFile);
    if (read != (xSize * ySize / 4)) {
		printf("EOF or Error\n");
	}
    read = fread(v, sizeof(char), xSize * ySize / 4, ptYuvFile);
    if (read != (xSize * ySize / 4)) {
		printf("EOF or Error\n");
	}
}

void closeYuvFile(){
    fclose(ptYuvFile);
}
