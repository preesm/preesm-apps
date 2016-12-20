/**
* Stabilization contains all functions needed to:
* - Find the motion resulting from camera shaking in a video.
* - Render a frame where this motion is compensated.
*
* @file stabilization.c
* @author kdesnos
* @date 2016.09.01
* @version 1.0
* @copyright CECILL-C
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#include "stabilization.h"

void renderFrame(const int frameWidth, const int frameHeight,
				 const int dispWidth, const int dispHeight,
				 const coordf * const delta,
				 const unsigned char * const yIn, const unsigned char * const uIn, const unsigned char * const vIn,
				 unsigned char * const yOut, unsigned char * const uOut, unsigned char * const vOut){

	// Set the background color
	memset(yOut, BG_BLACK_Y, dispWidth*dispHeight);
	memset(uOut, BG_BLACK_U, dispWidth*dispHeight / 4);
	memset(vOut, BG_BLACK_V, dispWidth*dispHeight / 4);

	// Compute the position of the rendered frame 
	// top-left (first pixel position)
	int xLeft = dispWidth / 2 - frameWidth / 2 + (int)roundf(delta->x);
	int yTop = dispHeight / 2 - frameHeight / 2 + (int)roundf(delta->y);
	// bottom right corner (last pixel position +(1,1))
	int xRight = xLeft + frameWidth;
	int yBot = yTop + frameHeight;

	// Clip previous values to stay within the rendered frame
	int xLeftClip = MAX(MIN(xLeft, dispWidth), 0);
	int yTopClip = MAX(MIN(yTop, dispHeight), 0);
	int xRightClip = MIN(MAX(xRight, 0), dispWidth);
	int yBotClip = MIN(MAX(yBot, 0), dispHeight);

	// Render Y
	for (int y = yTopClip; y < yBotClip; y++){
		memcpy(yOut + y*dispWidth + xLeftClip,
			   yIn + (y - yTop)*frameWidth + (xLeftClip - xLeft),
			   xRightClip - xLeftClip);
	}

	// Render UV
	for (int y = yTopClip / 2; y < yBotClip / 2; y++){
		memcpy(uOut + y*dispWidth / 2 + xLeftClip / 2,
			   uIn + (y - yTop / 2)*frameWidth / 2 + (xLeftClip - xLeft) / 2,
			   (xRightClip - xLeftClip) / 2);
		memcpy(vOut + y*dispWidth / 2 + xLeftClip / 2,
			   vIn + (y - yTop / 2)*frameWidth / 2 + (xLeftClip - xLeft) / 2,
			   (xRightClip - xLeftClip) / 2);
	}
}

void computeBlockMotionVectors(const int width, const int height,
							   const int blockWidth, const int blockHeight,
							   const int maxDeltaX, const int maxDeltaY,
							   const unsigned char * const frame, const unsigned char * const previousFrame,
							   coord * const vectors){
	// Useful constant
	const int blocksPerLine = width / blockWidth;

	// Divide into blocks
	block *blocks;
	blocks = malloc((width / blockWidth)*(height / blockHeight)*sizeof(block));
	divideBlocks(width, height, blockWidth, blockHeight, frame, blocks);

	// Process the blocks one by one
	for (int blY = 0; blY < (height / blockHeight); blY++){
		for (int blX = 0; blX < (width / blockWidth); blX++){
			const block* const b = blocks + blY*blocksPerLine + blX;
			computeBlockMotionVector(width, height,
									 blockWidth, blockHeight,
									 maxDeltaX, maxDeltaY,
									 b, previousFrame,
									 vectors + blY*blocksPerLine + blX);
		}
	}

	// Free blocks memory
	free(blocks);
}


unsigned int computeMeanSquaredError(const int width, const int height,
									 const int blockWidth, const int blockHeight,
									 const int deltaX, const int deltaY,
									 const block * const b, const unsigned char * const previousFrame){
	// Clip previous values to stay within the previousFrame
	int yMinClip = MIN(MAX(0 - deltaY, 0), blockHeight);
	int xMinClip = MIN(MAX(0 - deltaX, 0), blockWidth);
	int yMaxClip = MAX(MIN(height - deltaY, blockHeight), 0);
	int xMaxClip = MAX(MIN(width - deltaX, blockWidth), 0);

	// Compute MSE
	unsigned int cost;

	// At least half of the block must be matched within previous frame to 
	// consider the cost as valid (otherwise, a small number of pixel might 
	// get "lucky" and get a low cost).
	int matchedSize = (yMaxClip - yMinClip)*(xMaxClip - xMinClip);
	if (matchedSize < blockHeight*blockWidth / 2) {
		cost = UINT_MAX;
	}
	else {
		cost = 0;
		for (int y = yMinClip; y < yMaxClip; y++){
			for (int x = yMinClip; x < xMaxClip; x++){
				const unsigned char pixBlock = *(b->pix + y*blockWidth + x);
				const unsigned char pixFrame = *(previousFrame + (deltaY * width + deltaX) + y * width + x);
				// Squared error
				short diff = pixFrame - pixBlock;
				cost += diff*diff;
			}
		}
		// Mean
		cost /= matchedSize;
	}

	return cost;
}

void computeBlockMotionVector(const int width, const int height,
							  const int blockWidth, const int blockHeight,
							  const int maxDeltaX, const int maxDeltaY,
							  const block * const b, const unsigned char * const previousFrame,
							  coord * const vector){
	// Compute neighboorhood start positions
	// Top-left 
	int deltaYTop = b->coordinates.y - maxDeltaY;
	int deltaXLeft = b->coordinates.x - maxDeltaX;
	// Bottom-right +(1,1)
	int deltaYBot = b->coordinates.y + maxDeltaY;
	int deltaXRight = b->coordinates.x + maxDeltaX;

	// Initialize MMSE search
	unsigned int minCost = UINT_MAX;
	vector->x = 0;
	vector->y = 0;
	// Raster scan neighborhood
	for (int deltaY = deltaYTop; deltaY < deltaYBot; deltaY++){
		for (int deltaX = deltaXLeft; deltaX < deltaXRight; deltaX++){
			// Compute MSE
			unsigned int cost = computeMeanSquaredError(width, height,
														blockWidth, blockHeight,
														deltaX, deltaY,
														b, previousFrame);

			// Minimizes MSE
			if (cost < minCost){
				minCost = cost;
				vector->x = deltaX - b->coordinates.x;
				vector->y = deltaY - b->coordinates.y;
			}
		}
	}
}


void divideBlocks(const int width, const int height,
				  const int blockWidth, const int blockHeight,
				  const unsigned char * const frame,
				  block * const blocks){
	const int blocksPerLine = width / blockWidth;
	// Raster scan blocks
	for (int y = 0; y < height / blockHeight; y++){
		for (int x = 0; x < blocksPerLine; x++){
			block * b = blocks + y*(blocksPerLine)+x;
			b->coordinates.x = x*blockWidth;
			b->coordinates.y = y*blockHeight;
			// Copy block lines in output
			for (int line = 0; line < blockHeight; line++){
				memcpy(b->pix + line * blockWidth,
					   frame + (y*blockHeight + line)*width + x*blockWidth,
					   blockWidth);
			}
		}
	}
}

void findDominatingMotionVector(const int nbVectors,
								const coord * const vectors, coordf * const dominatingVector){
	static int first = 0;

	const unsigned char * pFrame;
	if (first == 0){
		first = 1;
		dominatingVector->x = 0;
		dominatingVector->y = 0;
	}
	else {
		// Compute multivariate gaussian parameters
		coordf mean;
		matrix sigma;
		meanVector(nbVectors, vectors, &mean);
		covarianceMatrix2D(nbVectors, vectors, &mean, &sigma);


		// Keep only the vectors with the highest probability
		// (criteria is a probability threshold, but a fixed number of vectors
		// could be used instead)
		float * probas = malloc(nbVectors*sizeof(nbVectors));
		getProbabilities(nbVectors, vectors, &mean, &sigma, probas);

		// Keep the mean of most probable vectors
		// find max proba
		float threshold = 0.0f;
		for (int i = 0; i < nbVectors; i++){
			threshold = MAX(threshold, probas[i]);
		}

		// Lower thresold
		threshold *= 2.0f / 3.0f;
		dominatingVector->x = 0.0f;
		dominatingVector->y = 0.0f;
		int nbAbove = 0;
		for (int i = 0; i < nbVectors; i++){
			if (probas[i] > threshold){
				nbAbove++;
				dominatingVector->x += vectors[i].x;
				dominatingVector->y += vectors[i].y;
			}
		}
		dominatingVector->x /= (float)nbAbove;
		dominatingVector->y /= (float)nbAbove;


		// Cleanup
		free(probas);
	}
}

void accumulateMotion(const coordf * const motionVector, const coordf * const accumulatedMotionIn, coordf * const accumulatedMotionOut){

	// Apply filter
	accumulatedMotionOut->x = accumulatedMotionIn->x * HIGH_PASS_FILTER_TAP;
	accumulatedMotionOut->y = accumulatedMotionIn->y * HIGH_PASS_FILTER_TAP;

	// Accumulate new motion vector
	accumulatedMotionOut->x += motionVector->x;
	accumulatedMotionOut->y += motionVector->y;
}