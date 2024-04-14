#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <stdint.h>

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct Color modifyColorIntensity(float k, struct Color c);
struct Color addColors(struct Color c1, struct Color c2);

#endif
