//
// Created by farresti on 31/10/17.
//

// std libs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
// SDL lib
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>

//#define FPS_MEAN 50

#include "../include/render.h"

#define PI 3.1415926535898f

extern int stopThreads;

int exitCallBack(void* userdata, SDL_Event* event){
    if (event->type == SDL_QUIT){
        printf("Exit request from GUI.\n");
        stopThreads = 1;
        return 0;
    }

    return 1;
}

typedef struct sdlDisplay {
    SDL_Renderer *renderer;
    SDL_Window *screen;
    SDL_Texture *texture;
//    TTF_Font *text_font;
}sdlDisplay;

static sdlDisplay display;

void renderInit(void) {
    display.screen = NULL;
    display.renderer = NULL;

    // Initialize SDL
    fprintf(stderr, "SDL_Init_Start\n");
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }
    fprintf(stderr, "SDL_Init_end\n");
    // Create window
    display.screen = SDL_CreateWindow("Environment_Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                     DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN);
    if (!display.screen) {
        fprintf(stderr, "SDL: could not set video mode - exiting\n");
        exit(1);
    }
    // Create renderer
    display.renderer = SDL_CreateRenderer(display.screen, -1, SDL_RENDERER_ACCELERATED);
    if (!display.renderer) {
        fprintf(stderr, "SDL: could not create renderer - exiting\n");
        exit(1);
    }
    SDL_Surface *surface = IMG_Load(PATH);

    if(!surface) {
        fprintf(stderr, "IMG_Load: %s\n", IMG_GetError());
        exit(1);
    }

    display.texture = SDL_CreateTextureFromSurface(display.renderer,
                                                   surface);
    if (!display.texture) {
        fprintf(stderr, "SDL: could not create texture - exiting\n");
        exit(1);
    }

    fprintf(stderr, "register exit callback\n");
    SDL_SetEventFilter(exitCallBack, NULL);
}

void renderEnv(int size, float *state) {
    /* Select the color for drawing. It is set to red here. */
    SDL_SetRenderDrawColor(display.renderer, 255, 255, 255, 255);
    /* Clear the entire screen to our selected color. */
    SDL_RenderClear(display.renderer);

    // set color for the pendulum
    SDL_SetRenderDrawColor(display.renderer, 255, 0, 0, 255);

    SDL_Rect dest = {225, 250, 49, 234};
    SDL_Point center = {25, 15};
    float angle = 180.f - state[0] * 180.f / (PI);

    SDL_RenderCopyEx(display.renderer, display.texture, NULL, &dest, angle, &center, SDL_FLIP_NONE);

    SDL_RenderPresent(display.renderer);

    SDL_Event event;
    // Grab all the events off the queue.
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            default:
                break;
        }
    }

    usleep(24000);
}

void renderFinalize(void)
{
    SDL_DestroyTexture(display.texture);
    SDL_DestroyRenderer(display.renderer);
    SDL_DestroyWindow(display.screen);
}
