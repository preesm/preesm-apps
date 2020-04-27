//
// Created by farresti on 21/08/18.
//

#ifndef SQUEEZENET_C_DISPLAY_H
#define SQUEEZENET_C_DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>


typedef struct display_t {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *image;
    TTF_Font *font;
    int width;
    int height;
} display_t;

/**
 * @brief Initialize the SDL library to display results
 *
 * @param width   Width of the display to be initialized
 * @param height  Height of the display to be initialized
 * @param display Display to be initialized
 * @return 0 on SUCCESS, -1 on ERROR
 */
int initDisplay(int width, int height, display_t *display);

/**
 * @brief Display the image contained in the surface of the display
 *
 * @param display Pointer to the display structure
 */
void display(display_t *display);

/**
 * @brief Display the image contained in the surface of the display with a given text over it.
 *
 * @param display Pointer to the display structure
 * @param text    Text to display
 */
void displayWithText(display_t *display, const char *text);

/**
 * @brief Quit SDL and free every associated resource
 *
 * @param display Display to be free
 */
void endDisplay(display_t *display);

#endif //SQUEEZENET_C_DISPLAY_H
