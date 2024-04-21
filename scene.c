#include "scene.h"

#include "vector.h"
#include "color.h"

const float VIEWPORT_WIDTH = 1;
const float VIEWPORT_HEIGHT = VIEWPORT_WIDTH;
const float VIEWPORT_DISTANCE = VIEWPORT_WIDTH;

const struct Vector CAMERA_POSITION = {0, 0, 0};
const struct Matrix CAMERA_ROTATION = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

const struct Color BACKGROUND_COLOR = {0, 0, 0};

const struct Sphere SPHERES[4] = {
	{ {0, -1, 3}, 1, {255, 0, 0}, 500, 0.2 },
	{ {2, 0, 4}, 1, {0, 0, 255}, 500, 0.3 },
	{ {-2, 0, 4}, 1, {0, 255, 0}, 10, 0.4 },
	{ {0, -5001, 0}, 5000, {255, 255, 0}, 1000, 0.5 }
};

const struct Light LIGHTS[3] = {
	{ LIGHT_AMBIENT, 0.2, {0, 0, 0} },
	{ LIGHT_POINT, 0.6, {2, 1, 0} },
	{ LIGHT_DIRECTIONAL, 0.2, {1, 4, 4} }
};
