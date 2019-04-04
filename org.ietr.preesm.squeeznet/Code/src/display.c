//
// Created by farresti on 21/08/18.
//

#include "display.h"
#include "common.h"

int initDisplay(int width, int height, display_t *display) {
    if (!display) {
        fprintf(stderr, "ERROR: Null pointer passed.\n");
        return -1;
    }

    if (width <= 0 || height <= 0) {
        fprintf(stderr, "ERROR: Invalid size for display init.\n");
        fprintf(stderr, "       |--> Width: %d  --  Height: %d\n", width, height);
        return -1;
    }


    // 1. Set everything to null by default
    display->renderer = NULL;
    display->window = NULL;
    display->image = NULL;
    display->font = NULL;
    display->width = width;
    display->height = height;

    // 2. Init SDL library
    /* Initialize SDL */
    printINFOVerbose("SDL_Init --> START\n");
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "ERROR: Could not initialize SDL:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        return -1;
    }
    printINFOVerbose("SDL_Init --> SUCCESS\n");

    /* Initialize SDL TTF for text display */
    printINFOVerbose("TTF_Init --> START\n");
    if (TTF_Init()) {
        fprintf(stderr, "ERROR: Could not initialize TTF:\n");
        fprintf(stderr, "       %s\n", TTF_GetError());
        endDisplay(display);
        return -1;
    }
    printINFOVerbose("TTF_Init --> SUCCESS\n");

    // 3. Initializing window and renderer
    /* Creates the window */
    display->window = SDL_CreateWindow("SqueezeNet-Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       display->width, display->height, SDL_WINDOW_SHOWN);
    if (!display->window) {
        fprintf(stderr, "ERROR: Failed to create window:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        endDisplay(display);
        return -1;
    }
    printINFOVerbose("SDL_CreateWindow --> SUCCESS\n");

    /* Creates the renderer */
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    if (!display->renderer) {
        fprintf(stderr, "ERROR: Failed to create renderer:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        endDisplay(display);
        return -1;
    }
    printINFOVerbose("SDL_CreateRenderer --> SUCCESS\n");

    /* Creates the surface */
    display->image = SDL_CreateRGBSurface(0, width, height, 24, 0, 0, 0, 0);
    if (!display->image) {
        fprintf(stderr, "ERROR: Failed to create image:\n");
        fprintf(stderr, "       %s\n", SDL_GetError());
        endDisplay(display);
        return -1;
    }
    printINFOVerbose("SDL_CreateRGBSurface --> SUCCESS\n");

    /* Open font */
    display->font = TTF_OpenFont(DEFAULT_PATH_FONT, 20);
    if (!display->font) {
        fprintf(stderr, "ERROR: Failed to open font:\n");
        fprintf(stderr, "       %s\n", TTF_GetError());
        endDisplay(display);
        return -1;
    }
    printINFOVerbose("TTF_OpenFont --> SUCCESS\n");

    printINFOVerbose("initDisplay --> SUCCESS.\n");
    return 0;
}

void display(display_t *display) {
    if (display) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(display->renderer, display->image);
        SDL_RenderCopy(display->renderer, texture, NULL, NULL);
        SDL_RenderPresent(display->renderer);
        SDL_DestroyTexture(texture);
    }
}

void displayWithText(display_t *display, const char *text) {
    if (display) {
        /* Render image */
        SDL_Texture *texture = SDL_CreateTextureFromSurface(display->renderer, display->image);
        SDL_RenderCopy(display->renderer, texture, NULL, NULL);

        /* Render Text */
        SDL_Color color_green = { 0, 255, 0, 255 };
        SDL_Surface* text_surface = TTF_RenderText_Blended(display->font, text, color_green);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(display->renderer, text_surface);

        int text_width = 0;
        int text_height = 0;
        SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);
        SDL_Rect text_rect;

        text_rect.x = 0;
        text_rect.y = 0;
        text_rect.w = text_width;
        text_rect.h = text_height;
        SDL_RenderCopy(display->renderer, text_texture, NULL, &text_rect);

        /* Render */
        SDL_RenderPresent(display->renderer);

        /* Free resources */
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }
}


void endDisplay(display_t *display) {
    /* Freeing resources of the display */
    if (display) {
        if (display->image) {
            SDL_FreeSurface(display->image);
        }
        if (display->window) {
            SDL_DestroyWindow(display->window);
        }
        if (display->renderer) {
            SDL_DestroyRenderer(display->renderer);
        }
        if (display->font) {
            TTF_CloseFont(display->font);
        }
    }


    /* Ending TTF + SDL */
    TTF_Quit();
    SDL_Quit();

    printINFOVerbose("endDisplay --> SUCCESS.\n");
}