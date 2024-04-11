#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

extern const char* CANVAS_TITLE;
extern const int CANVAS_WIDTH;
extern const int CANVAS_HEIGHT;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

struct color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct color modifyColorIntensity(float k, struct color c);
struct color addColors(struct color c1, struct color c2);

void setupCanvas();
void putPixel(int x, int y, struct color c);
void displayCanvas();
bool windowClosed();
void cleanupCanvas();

#endif
