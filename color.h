#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <stdint.h>

struct color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct color modifyColorIntensity(float k, struct color c);
struct color addColors(struct color c1, struct color c2);

#endif
