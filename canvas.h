#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

#include "color.h"

extern const char* CANVAS_TITLE;
extern const int CANVAS_WIDTH;
extern const int CANVAS_HEIGHT;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void setupCanvas();
void putPixel(int x, int y, struct Color c);
void displayCanvas();
bool windowClosed();
void cleanupCanvas();

#endif
