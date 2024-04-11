#include "canvas.h"

#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

const char* CANVAS_TITLE = "Computer Graphics from Scratch";
const int CANVAS_WIDTH = 600;
const int CANVAS_HEIGHT = CANVAS_WIDTH;

SDL_Window* window;
SDL_Renderer* renderer;

uint8_t modifyColorChannelIntensity(float k, uint8_t x) {
	float kx = k * x;
	kx += 0.5;
	if (kx >= 255)
		return 255;
	return (uint8_t) (kx);
}

struct color modifyColorIntensity(float k, struct color c) {
	struct color scaledColor = {
		modifyColorChannelIntensity(k, c.r),
		modifyColorChannelIntensity(k, c.g),
		modifyColorChannelIntensity(k, c.b)
	};
	return scaledColor;
}

uint8_t addColorChannels(uint8_t x, uint8_t y) {
	if (255-x < y)
		return 255;
	return x + y;
}

struct color addColors(struct color c1, struct color c2) {
	struct color colorSum = {
		addColorChannels(c1.r, c2.r),
		addColorChannels(c1.g, c2.g),
		addColorChannels(c1.b, c2.b)
	};
	return colorSum;
}

void setupCanvas() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(CANVAS_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CANVAS_WIDTH, CANVAS_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

void putPixel(int x, int y, struct color c) {
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
