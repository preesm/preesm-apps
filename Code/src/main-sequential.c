#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "applicationParameters.h"
#include "yuvDisplay.h" 
#include "yuvRead.h"	
#include "yuvWrite.h"
#include "stabilization.h"
#include "md5.h"

// #define VERBOSE
#ifdef VERBOSE
#include <stdio.h>
#endif

int stopThreads = 0;

int main(int argc, char** argv)
{
	// Declarations
	static unsigned char y[HEIGHT*WIDTH], u[HEIGHT*WIDTH / 4], v[HEIGHT*WIDTH / 4];
	static unsigned char yPrevious[HEIGHT*WIDTH];
	static unsigned char yDisp[DISPLAY_W*DISPLAY_H], uDisp[DISPLAY_W*DISPLAY_H / 4], vDisp[DISPLAY_W*DISPLAY_H / 4];
	static coord motionVectors[(HEIGHT / BLOCK_HEIGHT)*(WIDTH / BLOCK_WIDTH)];
	static coordf dominatingMotionVector;
	static coordf accumulatedMotion = { 0.0f, 0.0f };

	// Init display
	yuvDisplayInit(0, DISPLAY_W, DISPLAY_H);

	// Open files
	initReadYUV(WIDTH, HEIGHT);
	initYUVWrite();

	unsigned int frameIndex = 1;
	while (!stopThreads)
	{
		// Backup previous frame
		memcpy(yPrevious, y, HEIGHT*WIDTH);

		// Read a frame
		readYUV(WIDTH, HEIGHT, y, u, v);

		// Compute motion vectors
		computeBlockMotionVectors(WIDTH, HEIGHT,
								  BLOCK_WIDTH, BLOCK_HEIGHT,
								  MAX_DELTA_X, MAX_DELTA_Y,
								  y, yPrevious,
								  motionVectors);

		// Find dominating motion vector
		const int nbVectors = (HEIGHT / BLOCK_HEIGHT)*(WIDTH / BLOCK_WIDTH);
		findDominatingMotionVector(nbVectors,
								   motionVectors, &dominatingMotionVector);
		#ifdef VERBOSE
		// Print motion vector
		printf("Frame %3d: %2.2f, %2.2f\n", frameIndex,
			   dominatingMotionVector.x, dominatingMotionVector.y);
		#endif

		// Accumulate motion
		accumulateMotion(&dominatingMotionVector, &accumulatedMotion, &accumulatedMotion);

		// Render the motion compensated frame
		renderFrame(WIDTH, HEIGHT, DISPLAY_W, DISPLAY_H, &accumulatedMotion, y, u, v, yDisp, uDisp, vDisp);

		// Display it
		yuvDisplay(0, yDisp, uDisp, vDisp);

		// Compute the MD5 of the rendered frame
		MD5_Update(DISPLAY_H*DISPLAY_W, yDisp);

		// Save it
		yuvWrite(DISPLAY_W, DISPLAY_H, yDisp, uDisp, vDisp);

		// Exit ?
		frameIndex++;
		if (frameIndex == NB_FRAME){
			stopThreads = 1;
		}
	}

	#ifdef VERBOSE
	printf("Exit program\n");
	#endif 
	yuvFinalize(0);
	endYUVRead();
	endYUVWrite();

	return 0;
}
