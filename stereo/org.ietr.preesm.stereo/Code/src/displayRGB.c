/*
	============================================================================
	Name        : displayRGB.c
	Author      : mpelcat & kdesnos
	Version     : 1.1
	Copyright   : CeCILL-C, IETR, INSA Rennes
	Description : Displaying RGB frames one next to another in a row
	============================================================================
	*/

#include <stdio.h>

#include "displayRGB.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <pthread.h>
#include <time.h>

#define FPS_MEAN 5

extern int preesmStopThreads;

/**
* Structure representing one display
*/
typedef struct RGBDisplay
{
	SDL_Texture* textures[NB_DISPLAY];	    // One overlay per frame
	SDL_Window *screen;					    // SDL window where to display
	SDL_Surface* surface[NB_DISPLAY];
	SDL_Renderer *renderer;
	TTF_Font *text_font;
	int currentXMin;						// Position for next display
	int initialized;                        // Initialization done ?
	int stampId;
} RGBDisplay;


// Initialize
static RGBDisplay display ;

int exitCallBack(void* userdata, SDL_Event* event){
	if (event->type == SDL_QUIT){
		printf("Exit request from GUI.\n");
		preesmStopThreads = 1;
		return 0;
	}

	return 1;
}

void displayRGBInit(int id, int height, int width){
	if (display.initialized == 0)
	{
		display.currentXMin = 0;
	}

	if (height > DISPLAY_H)
	{
		fprintf(stderr, "SDL screen is not high enough for display %d.\n", id);
		exit(1);
	}
	else if (id >= NB_DISPLAY)
	{
		fprintf(stderr, "The number of displays is limited to %d.\n", NB_DISPLAY);
		exit(1);
	}
	else if (display.currentXMin + width > DISPLAY_W)
	{
		fprintf(stderr, "The number is not wide enough for display %d.\n", NB_DISPLAY);
		exit(1);
	}


#ifdef PREESM_VERBOSE
	printf("SDL screen height OK, width OK, number of displays OK.\n");
#endif

	if (display.initialized == 0)
	{
		// Generating window name
		char* name = "Display";
		display.initialized = 1;

		SDL_SetEventFilter(exitCallBack, NULL);

		if (SDL_Init(SDL_INIT_VIDEO))
		{
			fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
			exit(1);
		}

		printf("SDL_Init_end\n");

		/* Initialize SDL TTF for text display */
		if (TTF_Init())
		{
			printf("TTF initialization failed: %s\n", TTF_GetError());
		}

		printf("TTF_Init\n");

		/* Initialize Font for text display */
		display.text_font = TTF_OpenFont(PATH_TTF, 20);
		if (!display.text_font)
		{
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}

		display.screen = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										  DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN);
		if (!display.screen)
		{
			fprintf(stderr, "SDL: could not set video mode - exiting\n");
			exit(1);
		}

		display.renderer = SDL_CreateRenderer(display.screen, -1, SDL_RENDERER_ACCELERATED);
		if (!display.renderer)
		{
			fprintf(stderr, "SDL: could not create renderer - exiting\n");
			exit(1);
		}
	}

	if (display.textures[id] == NULL)
	{

		display.textures[id] = SDL_CreateTexture(display.renderer,
												 SDL_PIXELFORMAT_RGB888,
												 SDL_TEXTUREACCESS_STREAMING,
												 width, height);

		if (!display.textures[id])
		{
			fprintf(stderr, "SDL: could not create texture - exiting\n");
			exit(1);
		}

		display.currentXMin += width;
	}

	if (display.surface[id] == NULL){
		display.surface[id] = SDL_CreateRGBSurface(0, width, height, 32,0,0,0,0);
		if (!display.surface[id])
		{
			fprintf(stderr, "SDL: could not create surface - exiting\n");
			exit(1);
		}
	}

	if (id == 0){
		display.stampId = 1;
		for (int i = 1; i<FPS_MEAN+1; i++){
			startTiming(i);
		}
	}

}

void displayLum(int id, unsigned char *lum){
	int idxPxl,w,h;
	SDL_Texture* texture = display.textures[id];
	SDL_Surface *surface = display.surface[id];

	// Prepare RGB texture
	// Retrieve texture attribute
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	for (idxPxl = 0; idxPxl < h*w; idxPxl++){
		*(((char*)(surface->pixels)) + 4 * idxPxl)	   = *(lum + idxPxl);
		*(((char*)(surface->pixels)) + 4 * idxPxl + 1) = *(lum + idxPxl);
		*(((char*)(surface->pixels)) + 4 * idxPxl + 2) = *(lum + idxPxl);
	}

	refreshDisplayRGB(id);
}

void displayRGB(int id, int height, int width, unsigned char *rgb){

	int idxPxl, w, h;
	SDL_Texture* texture = display.textures[id];
	SDL_Surface *surface = display.surface[id];

	// Prepare RGB texture
	// Retrieve texture attribute
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	for (idxPxl = 0; idxPxl < h*w; idxPxl++){
		*(((char*)(surface->pixels)) + 4 * idxPxl + 0) = *(rgb + 3 * idxPxl + 2);
		*(((char*)(surface->pixels)) + 4 * idxPxl + 1) = *(rgb + 3 * idxPxl + 1);
		*(((char*)(surface->pixels)) + 4 * idxPxl + 2) = *(rgb + 3 * idxPxl + 0);
	}

	refreshDisplayRGB(id);
}


void refreshDisplayRGB(int id)
{
	SDL_Texture* texture = display.textures[id];
	SDL_Event event;
	SDL_Rect screen_rect;

	SDL_QueryTexture(texture, NULL, NULL, &(screen_rect.w), &(screen_rect.h));

	SDL_UpdateTexture(texture, NULL, display.surface[id]->pixels, screen_rect.w*4);

	screen_rect.x = screen_rect.w*id;
	screen_rect.y = 0;

	SDL_RenderCopy(display.renderer, texture, NULL, &screen_rect);

	/* Draw FPS text */
	if (id == 0){
		char fps_text[20];
		SDL_Color colorWhite = { 255, 255, 255, 255 };

		int time = stopTiming(display.stampId+1);
		sprintf(fps_text, "FPS: %.2f", 1. / (time / 1000000. / FPS_MEAN));
		startTiming(display.stampId+1);
		display.stampId = (display.stampId + 1) % FPS_MEAN;

		SDL_Surface* fpsText = TTF_RenderText_Blended(display.text_font, fps_text, colorWhite);
		SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(display.renderer, fpsText);

		int fpsWidth, fpsHeight;
		SDL_QueryTexture(fpsTexture, NULL, NULL, &fpsWidth, &fpsHeight);
		SDL_Rect fpsTextRect;

		fpsTextRect.x = 0;
		fpsTextRect.y = 0;
		fpsTextRect.w = fpsWidth;
		fpsTextRect.h = fpsHeight;
		SDL_RenderCopy(display.renderer, fpsTexture, NULL, &fpsTextRect);

		/* Free resources */
		SDL_FreeSurface(fpsText);
		SDL_DestroyTexture(fpsTexture);
	}

	SDL_RenderPresent(display.renderer);

	// Grab all the events off the queue.
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		default:
			break;
		}
	}
}

void finalizeRGB(int id)
{
	SDL_FreeSurface(display.surface[id]);
	SDL_DestroyTexture(display.textures[id]);
	SDL_DestroyRenderer(display.renderer);
	SDL_DestroyWindow(display.screen);
}
