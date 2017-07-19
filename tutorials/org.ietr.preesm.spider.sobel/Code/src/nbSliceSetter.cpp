/*
	============================================================================
	Name        : nbSliceSetter.cpp
	Author      : jheulot
	Version     :
	Copyright   : CECILL-C
	Description : Set nbSlice Parameter
	============================================================================
*/

#include "nbSliceSetter.h"
	
#include <stdio.h>
#include <time.h>
#include <SDL.h>

#define MAX_NB_CONFIG 20

extern int stopThreads;

int configs[MAX_NB_CONFIG];
int nbConfigs = 0;

int currentConfig;

void initNbSliceSetter(Param height){
	// Fill the configs table with all valid values for nbSlice.
	// Only integer divisor of height are considered as valid values
	int testedSlice = 1;
	while (nbConfigs<MAX_NB_CONFIG && testedSlice < height){
		if ((height % testedSlice) == 0)
			configs[nbConfigs++] = testedSlice;
		testedSlice++;
	}

	currentConfig = nbConfigs / 2;
}

void nbSliceSetter (Param height, Param* nbSlice){
	SDL_Event event;
	
	// Grab all the events off the queue.
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			stopThreads = 1;
			break;
		case SDL_KEYDOWN:
			
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_KP_PLUS)
			{
				currentConfig = (currentConfig + 1 < nbConfigs) ? currentConfig + 1 : currentConfig;
			}
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_KP_MINUS)
			{
				currentConfig = (currentConfig - 1 > -1) ? currentConfig - 1 : currentConfig;
			}
			printf("NbSlice = %d\n", configs[currentConfig]);

		default:
			break;
		}
	}

	*nbSlice = configs[currentConfig];
}
