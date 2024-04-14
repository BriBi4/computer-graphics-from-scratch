#include "color.h"

#include <stdint.h>

uint8_t modifyColorChannelIntensity(float k, uint8_t x) {
	float kx = k * x;
	kx += 0.5;
	if (kx >= 255)
		return 255;
	return (uint8_t) (kx);
}

struct Color modifyColorIntensity(float k, struct Color c) {
	struct Color scaledColor = {
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

struct Color addColors(struct Color c1, struct Color c2) {
	struct Color colorSum = {
		addColorChannels(c1.r, c2.r),
		addColorChannels(c1.g, c2.g),
		addColorChannels(c1.b, c2.b)
	};
	return colorSum;
}
