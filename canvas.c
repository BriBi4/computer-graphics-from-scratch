#include "canvas.h"

#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

#include "color.h"

const char* CANVAS_TITLE = "Computer Graphics from Scratch";
const int CANVAS_WIDTH = 600;
const int CANVAS_HEIGHT = CANVAS_WIDTH;

SDL_Window* window;
SDL_Renderer* renderer;

void setupCanvas() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(CANVAS_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CANVAS_WIDTH, CANVAS_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

void putPixel(int x, int y, struct Color c) {
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
	int xPos = (CANVAS_WIDTH/2) + x;
	int yPos = (CANVAS_HEIGHT/2) - y;
	SDL_RenderDrawPoint(renderer, xPos, yPos);
}

void displayCanvas() {
	SDL_RenderPresent(renderer);
}

bool windowClosed() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return true;
	}
	return false;
}

void cleanupCanvas() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
