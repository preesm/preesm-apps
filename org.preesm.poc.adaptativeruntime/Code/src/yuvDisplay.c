/*
 ============================================================================
 Name        : displayYUV.c
 Author      : mpelcat & kdesnos & jheulot
 Version     :
 Copyright   : CECILL-C
 Description : Displaying YUV frames one next to another in a row
 ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "yuvDisplay.h"
#include "clock.h"
#include "energyMonitor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <semaphore.h>

#define FPS_MEAN 1
#define FPS_LIMIT 1.8

#define ENERGY_MEAN 30
static float energyMeasuresA15[ENERGY_MEAN];
static float energyMeasuresA7[ENERGY_MEAN];

extern int stopThreads;

/**
 * Structure representing one display
 */
typedef struct YuvDisplay {
	SDL_Texture* textures[NB_DISPLAY];	    // One overlay per frame
	SDL_Window *screen;					    // SDL surface where to display
	SDL_Renderer *renderer;
	TTF_Font *text_font;
	int currentXMin;						// Position for next display
	int initialized;                        // Initialization done ?
	int stampId;
} YuvDisplay;

// Initialize
static YuvDisplay display;
static sem_t framerate_controller;

int exitCallBack(void* userdata, SDL_Event* event) {
	if (event->type == SDL_QUIT) {
		printf("Exit request from GUI.\n");
		stopThreads = 1;
		return 0;
	}

	return 1;
}

static SDL_TimerID timerID;

unsigned int timerCallBack(unsigned int interval, void* param) {
	int val;
	sem_getvalue(&framerate_controller, &val);
	if (val == 0) {
		sem_post(&framerate_controller);
	} else {
		printf("FAIL\n");
	}
	return 0;
}

/**
 * Initializes a display frame. Be careful, once a window size has been chosen,
 * all videos must share the same window size
 *
 * @param id display unique identifier
 * @param width width
 * @param height heigth
 */
void yuvDisplayInit(int id, int width, int height) {

	if (display.initialized == 0) {
		display.currentXMin = 0;
	}

	if (height > DISPLAY_H) {
		fprintf(stderr, "SDL screen is not high enough for display %d.\n", id);
		system("PAUSE");
		exit(1);
	} else if (id >= NB_DISPLAY) {
		fprintf(stderr, "The number of displays is limited to %d.\n",
		NB_DISPLAY);
		system("PAUSE");
		exit(1);
	} else if (display.currentXMin + width > DISPLAY_W) {
		fprintf(stderr, "The number is not wide enough for display %d.\n",
		NB_DISPLAY);
		system("PAUSE");
		exit(1);
	}

#ifdef VERBOSE
	printf("SDL screen height OK, width OK, number of displays OK.\n", id);
#endif

	if (display.initialized == 0) {
		// Generating window name
		const char* name = "Display";
		display.initialized = 1;

		printf("SDL_Init_Start\n");

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
			fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
			exit(1);
		}

		printf("SDL_Init_end\n");

		/* Initialize SDL TTF for text display */
		if (TTF_Init()) {
			printf("TTF initialization failed: %s\n", TTF_GetError());
		}

		printf("TTF_Init\n");

		/* Initialize Font for text display */
		display.text_font = TTF_OpenFont(PATH_TTF, 20);
		if (!display.text_font) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}

		display.screen = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN);
		if (!display.screen) {
			fprintf(stderr, "SDL: could not set video mode - exiting\n");
			exit(1);
		}

		display.renderer = SDL_CreateRenderer(display.screen, -1,
				SDL_RENDERER_ACCELERATED);
		if (!display.renderer) {
			fprintf(stderr, "SDL: could not create renderer - exiting\n");
			exit(1);
		}
	}

	if (display.textures[id] == NULL) {

		display.textures[id] = SDL_CreateTexture(display.renderer,
				SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width,
				height);

		if (!display.textures[id]) {
			fprintf(stderr, "SDL: could not create texture - exiting\n");
			exit(1);
		}

		display.currentXMin += width;
	}

	display.stampId = 0;
	for (int i = 0; i < FPS_MEAN; i++) {
		startTiming(i + 1);
	}

	for (int i = 0; i < ENERGY_MEAN; i++) {
		energyMeasuresA15[i] = 0.0;
		energyMeasuresA7[i] = 0.0;
	}

	printf("register\n");
	SDL_SetEventFilter(exitCallBack, NULL);

	// Initialize Energy Monitoring
	initEnergyMonitoring();

	// Set timer for framerate limitation
	sem_init(&framerate_controller, 0, 0);
	timerID = SDL_AddTimer(1000 / FPS_LIMIT, timerCallBack, (void*) NULL);
}

void yuvDisplay(int id, unsigned char *y, unsigned char *u, unsigned char *v) {
	yuvDisplayWithNbSlice(id, -1, y, u, v);
}

void displayText(const char * text, int posX, int posY){
	SDL_Color colorWhite = { 255, 255, 255, 255 };

	SDL_Surface* textSurf = TTF_RenderText_Blended(display.text_font, text,
			colorWhite);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(display.renderer,
			textSurf);

	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	SDL_Rect textRect;

	textRect.x = posX;
	textRect.y = posY;
	textRect.w = width;
	textRect.h = height;
	SDL_RenderCopy(display.renderer, texture, NULL, &textRect);

	/* Free resources */
	SDL_FreeSurface(textSurf);
	SDL_DestroyTexture(texture);
}

void yuvDisplayWithNbSlice(int id, int nbSlice, unsigned char *y,
		unsigned char *u, unsigned char *v) {
	SDL_Texture* texture = display.textures[id];
	int w, h;
	sensors data;
	static int energyIdx = 0;

	// Retrieve texture attribute
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_UpdateYUVTexture(texture, NULL, y, w, u, w / 2, v, w / 2);

	SDL_Rect screen_rect;

	screen_rect.w = w;
	screen_rect.h = h;
	screen_rect.x = w * id;
	screen_rect.y = 0;

	SDL_RenderCopy(display.renderer, texture, NULL, &screen_rect);

	/* Draw FPS text */
	char fps_text[20];


	sem_wait(&framerate_controller);
	timerID = SDL_AddTimer(1000 / FPS_LIMIT, timerCallBack, (void*) NULL);

	int time = stopTiming(display.stampId + 1);
	sprintf(fps_text, "%.2f", 1. / (time / 1000000. / FPS_MEAN));
	startTiming(display.stampId + 1);
	display.stampId = (display.stampId + 1) % FPS_MEAN;

	displayText("FPS:", 4, 2);
	displayText(fps_text, 55, 2);

	// Get power info
	getSensorsData(&data);

	energyMeasuresA15[energyIdx] = data.a15.w;
	energyMeasuresA7[energyIdx] = data.a7.w;
	energyIdx = (energyIdx + 1) % ENERGY_MEAN;
	float a15w = 0;
	float a7w = 0;
	for (int i = 0; i < ENERGY_MEAN; i++) {
		a15w += energyMeasuresA15[i] / ENERGY_MEAN;
		a7w += energyMeasuresA7[i] / ENERGY_MEAN;
	}

	char wtext[40];


	sprintf(wtext, "%1.2f", a15w);
	displayText("A15:", 4, 22);
	displayText(wtext, 55, 22);
	sprintf(wtext, "%1.2f", a7w);
	displayText("A7:", 4, 42);
	displayText(wtext, 55, 42);

	//printf("A15: %f A7: %f\n", a15w, a7w);

	SDL_RenderPresent(display.renderer);

	SDL_Event event;
	// Grab all the events off the queue.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		default:
			break;
		}
	}

}



void yuvFinalize(int id) {
	stopEnergyMonitoring();
	SDL_RemoveTimer(timerID);
	SDL_DestroyTexture(display.textures[id]);
	SDL_DestroyRenderer(display.renderer);
	SDL_DestroyWindow(display.screen);
}
