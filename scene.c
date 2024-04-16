#include "scene.h"

#include "vector.h"
#include "color.h"

const float VIEWPORT_WIDTH = 1;
const float VIEWPORT_HEIGHT = VIEWPORT_WIDTH;
const float VIEWPORT_DISTANCE = VIEWPORT_WIDTH;

const struct Vector CAMERA_POSITION = {0, 0, 0};

const struct Color BACKGROUND_COLOR = {255, 255, 255};

const struct Sphere SPHERES[3] = {
	{ {0, -1, 3}, 1, {255, 0, 0} },
	{ {2, 0, 4}, 1, {0, 0, 255} },
	{ {-2, 0, 4}, 1, {0, 255, 0} }
};

const struct Light LIGHTS[3] = {
	{ LIGHT_AMBIENT, 0.2, {0, 0, 0} },
	{ LIGHT_POINT, 0.6, {2, 1, 0} },
	{ LIGHT_DIRECTIONAL, 0.2, {1, 4, 4} }
};
