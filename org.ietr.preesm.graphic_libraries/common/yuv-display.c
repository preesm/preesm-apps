/*
 * Copyright or © or Copr. IETR/INSA - Rennes (2013 - 2019) :
 *
 * Antoine Morvan <antoine.morvan@insa-rennes.fr> (2018)
 * Clément Guy <clement.guy@insa-rennes.fr> (2014)
 * Florian Arrestier <florian.arrestier@insa-rennes.fr> (2017-2019)
 * Hugo Miomandre <hugo.miomandre@insa-rennes.fr> (2017)
 * Julien Heulot <julien.heulot@insa-rennes.fr> (2013 - 2015)
 * Yaset Oliva <yaset.oliva@insa-rennes.fr> (2013 - 2014)
 * Karol Desnos <karol.desnos@insa-rennes.fr> (2013-2020)
 * Maxime Pelcat <karol.desnos@insa-rennes.fr> (2013-2020)
 *
 * This software is governed by the CeCILL  license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "yuv-display.h"
#include "clock.h"


extern int preesmStopThreads;

/**
* Structure representing one display
*/
typedef struct {
    SDL_Texture *textures[NB_DISPLAY]; /*!< SDL texture used for final rendering with hardware acceleration */
    SDL_Window *screen;                /*!< SDL window used for this display */
    SDL_Renderer *renderer;            /*!< SDL renderer used for rendering the textures in this display */
    TTF_Font *textFont;                /*!< TTF font used for rendering fps text */
    int currentXMin;                        // Position for next display
    int initialized;                        // Initialization done ?
    int stampId;
} display_t;


// Initialize

/* === Static variables === */
static SDL_Color colorWhite = { .r = 255, .g = 255, .b = 255, .a = 255 };

static display_t display = {
        .textures = { NULL },
        .screen = NULL,
        .renderer = NULL,
        .textFont = NULL,
        .currentXMin = 0,
        .initialized = 0,
        .stampId = 0 };

/* === Static functions === */

/**
 * @brief Cleanup all resources related to SDL.
 */
static void cleanUpSDL(void) {
    if (display.textFont) {
        TTF_CloseFont(display.textFont);
        TTF_Quit();
    }
    for (int i = 0; i < NB_DISPLAY; ++i) {
        if (display.textures[i]) {
            SDL_DestroyTexture(display.textures[i]);
        }
    }
    if (display.screen) {
        SDL_DestroyWindow(display.screen);
    }
    if (display.renderer) {
        SDL_DestroyRenderer(display.renderer);
    }
    SDL_Quit();
}

/**
 * @brief Call back
 * @param userdata  Pointer to data when exiting (used for clean SDL_quit).
 * @param event     Pointer to the event.
 * @return 0 if exit event is caught, 1 else.
 */
static int exitCallBack(void *userdata, SDL_Event *event) {
    (void) (userdata);
    if (event->type == SDL_QUIT) {
        fprintf(stderr, "Exit request from GUI.\n");
        preesmStopThreads = 1;
        cleanUpSDL();
        exit(0);
    }
    return 1;
}

void yuvDisplayInit(int id, int width, int height, int displayWidth, int displayHeight) {
    if (id >= NB_DISPLAY) {
        fprintf(stderr, "ERROR: Display id[%d] is not compatible with the number of display[%d].\n", id, NB_DISPLAY);
#ifdef _WIN32
        system("PAUSE");
#endif
        exit(1);
    }
    if (height > displayHeight) {
        fprintf(stderr,
                "WARNING: SDL screen height[%d] is smaller thant video height[%d], content will be shrunk to fit in display.\n",
                displayHeight, height);
    }
    if (display.currentXMin + width > displayWidth) {
        fprintf(stderr,
                "ERROR: SDL screen width [%d] is smaller than video width [%d], content can not fit in display.\n",
                displayWidth, display.currentXMin + width);
        exit(1);
    }
    if (!display.initialized) {
        display.initialized = 1;

        /* == Main window name == */
        const char *name = "PREESM-YUV-Display";
#ifdef VERBOSE
        fprintf(stderr, "VERB: SDL_Init start.\n");
#endif
        if (SDL_Init(SDL_INIT_VIDEO)) {
            fprintf(stderr, "ERROR: failed to initialize SDL: %s\n", SDL_GetError());
            exit(1);
        }
#ifdef VERBOSE
        fprintf(stderr, "VERB: SDL_Init end.\n");
        fprintf(stderr, "VERB: TTF_Init start.\n");
#endif
        /* == Initialize SDL TTF for text display == */
        if (TTF_Init()) {
            fprintf(stderr, "ERROR: failed to initialize TTF: %s\n", TTF_GetError());
            cleanUpSDL();
            exit(1);
        }
#ifdef VERBOSE
        fprintf(stderr, "VERB: TTF_Init end.\n");
#endif
        /* == Initialize Font for text display == */
        display.textFont = TTF_OpenFont(PATH_TTF, 20);
        if (!display.textFont) {
            fprintf(stderr, "ERROR: failed to open text font: %s\n", TTF_GetError());
            cleanUpSDL();
            exit(1);
        }

        display.screen = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth,
                                          displayHeight,
                                          SDL_WINDOW_SHOWN);
        if (!display.screen) {
            fprintf(stderr, "ERROR: failed to created main window: %s\n", SDL_GetError());
            cleanUpSDL();
            exit(1);
        }
        display.renderer = SDL_CreateRenderer(display.screen, -1, SDL_RENDERER_ACCELERATED);
        if (!display.renderer) {
            fprintf(stderr, "ERROR: failed to created main renderer: %s\n", SDL_GetError());
            cleanUpSDL();
            exit(1);
        }
    }

    if (!display.textures[id]) {
        display.textures[id] = SDL_CreateTexture(display.renderer,
                                                 SDL_PIXELFORMAT_IYUV,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 width, height);
        if (!display.textures[id]) {
            fprintf(stderr, "ERROR: failed to create texture: %s\n", SDL_GetError());
            cleanUpSDL();
            exit(1);
        }
        display.currentXMin += width;
    }

    display.stampId = 0;
    for (int i = 0; i < FPS_MEAN; i++) {
        startTiming(i + 1);
    }
    SDL_SetEventFilter(exitCallBack, NULL);
}

void yuvDisplay(int id, unsigned char *y, unsigned char *u, unsigned char *v) {
    yuvDisplayWithNbSlice(id, -1, y, u, v);
}

void yuvDisplayWithNbSlice(int id, int nbSlice, unsigned char *y, unsigned char *u, unsigned char *v) {
    SDL_Texture *texture = display.textures[id];
    if (!texture) {
        fprintf(stderr, "ERROR: texture for display id[%d] is NULL.\n", id);
        cleanUpSDL();
        exit(1);
    }

    /* ==  Retrieve texture attribute == */
    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    /* == Update texture from data == */
    SDL_UpdateYUVTexture(texture,
                         NULL,
                         y, width,
                         u, width / 2,
                         v, width / 2);

    /* == Copy the texture in the proper place in the display == */
    SDL_Rect screenRect = { .x = width * id, .y = 0, .w = width, .h = height };
    SDL_RenderCopy(display.renderer, texture, NULL, &screenRect);

    /* == Draw FPS text == */
    char fps_text[20];
    unsigned int time = stopTiming(display.stampId + 1);
    sprintf(fps_text, "FPS: %.2f", 1. / (time / 1000000. / FPS_MEAN));
    startTiming(display.stampId + 1);
    display.stampId = (display.stampId + 1) % FPS_MEAN;
    SDL_Surface *fpsText = TTF_RenderText_Blended(display.textFont, fps_text, colorWhite);
    SDL_Texture *fpsTexture = SDL_CreateTextureFromSurface(display.renderer, fpsText);

    int fpsWidth = 0;
    int fpsHeight = 0;
    SDL_QueryTexture(fpsTexture, NULL, NULL, &fpsWidth, &fpsHeight);
    SDL_Rect fpsTextRect = { .x = 0, .y = 0, .w = fpsWidth, .h = fpsHeight };
    SDL_RenderCopy(display.renderer, fpsTexture, NULL, &fpsTextRect);

    /* == Free resources == */
    SDL_FreeSurface(fpsText);
    SDL_DestroyTexture(fpsTexture);

    /* Draw NbSlice Text */
    if (nbSlice > 0) {
        char slice_text[20];

        sprintf(slice_text, "nbSlice: %d", nbSlice);

        SDL_Surface *sliceText = TTF_RenderText_Blended(display.textFont, slice_text, colorWhite);
        SDL_Texture *sliceTexture = SDL_CreateTextureFromSurface(display.renderer, sliceText);

        int sliceWidth = 0;
        int sliceHeight = 0;
        SDL_QueryTexture(sliceTexture, NULL, NULL, &sliceWidth, &sliceHeight);
        SDL_Rect sliceTextRect = { .x = 0, .y = fpsHeight, .w = sliceWidth, .h = sliceHeight };
        SDL_RenderCopy(display.renderer, sliceTexture, NULL, &sliceTextRect);

        /* == Free resources == */
        SDL_FreeSurface(sliceText);
        SDL_DestroyTexture(sliceTexture);
    }

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

void yuvFinalize() {
    cleanUpSDL();
}
