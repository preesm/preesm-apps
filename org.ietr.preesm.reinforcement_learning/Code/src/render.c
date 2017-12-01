//
// Created by farresti on 31/10/17.
//

// std libs
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// SDL libs
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <zconf.h>
// timing lib
#include "../include/clock.h"
// file header
#include "../include/render.h"

// file defines
#define FPS_MEAN 50
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
    TTF_Font *font;
    int stampId;
}sdlDisplay;

static sdlDisplay display;

void renderInit(void) {
    // Initializes random module
    srand((unsigned int)time(NULL));

    display.screen = NULL;
    display.renderer = NULL;

    // Initialize SDL
    fprintf(stderr, "SDL_Init_Start\n");
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }
    fprintf(stderr, "SDL_Init_End\n");


    // Initialize SDL TTF for text display
    fprintf(stderr, "SDL_TTF_Init_Start\n");
    if (TTF_Init()) {
        printf("TTF initialization failed: %s\n", TTF_GetError());
    }
    fprintf(stderr, "SDL_TTF_Init_End\n");

    // Open Font for text display
    display.font = TTF_OpenFont(PATH_TTF, 20);
    if (!display.font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

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

    display.stampId = 0;
    for (int i = 0; i < FPS_MEAN; ++i) {
        startTiming(i + 1);
    }

    fprintf(stderr, "register exit callback\n");
    SDL_SetEventFilter(exitCallBack, NULL);
}

void renderEnv(int size, float *state) {
    /* Select the color for drawing. It is set to red here. */
    SDL_SetRenderDrawColor(display.renderer, 255, 255, 255, 255);
    /* Clear the entire screen to our selected color. */
    SDL_RenderClear(display.renderer);

    // Position of the pendulum in the window
    SDL_Rect dest = {225, 250, 49, 234};
    SDL_Point center = {25, 15};
    // Convert the angle to degree with the offset to match the python training
    float angle = 180.f - state[0] * 180.f / (PI);
    // Display the pendulum
    SDL_RenderCopyEx(display.renderer, display.texture, NULL, &dest, angle, &center, SDL_FLIP_NONE);

    // Print FPS text
    char stringFPS[20];
    SDL_Color colorGreen = {0, 255, 0, 255};
    int timeStamp = stopTiming(display.stampId + 1);
    sprintf(stringFPS, "%.2f fps", 1. / (timeStamp / 1000000. / FPS_MEAN));
    startTiming(display.stampId + 1);
    display.stampId = (display.stampId + 1) % FPS_MEAN;

    SDL_Surface* surfaceFPS = TTF_RenderText_Blended(display.font, stringFPS, colorGreen);
    SDL_Texture* textureFPS = SDL_CreateTextureFromSurface(display.renderer, surfaceFPS);

    int widthFPS, heightFPS;
    SDL_QueryTexture(textureFPS, NULL, NULL, &widthFPS, &heightFPS);
    SDL_Rect rectFPSText = {0, 0, widthFPS, heightFPS};
    SDL_RenderCopy(display.renderer, textureFPS, NULL, &rectFPSText);

    // Free resources
    SDL_FreeSurface(surfaceFPS);
    SDL_DestroyTexture(textureFPS);

    // Proceed to the actual display
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

    // Sleep to smooth the rendering
//    usleep(500000);
//    sleep(1);
}

void renderFinalize(void)
{
    SDL_DestroyTexture(display.texture);
    SDL_DestroyRenderer(display.renderer);
    SDL_DestroyWindow(display.screen);
}
