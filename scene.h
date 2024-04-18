#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "vector.h"
#include "color.h"

#define LIGHT_AMBIENT 'a'
#define LIGHT_POINT 'p'
#define LIGHT_DIRECTIONAL 'd'

extern const float VIEWPORT_WIDTH;
extern const float VIEWPORT_HEIGHT;
extern const float VIEWPORT_DISTANCE;

extern const struct Vector CAMERA_POSITION;

extern const struct Color BACKGROUND_COLOR;

struct Sphere {
	struct Vector center;
	float radius;
	struct Color color;
	float specular;
	float reflective;
};

struct Light {
	char type;
	float intensity;
	struct Vector posOrDir;
};

extern const struct Sphere SPHERES[4];
extern const struct Light LIGHTS[3];

#endif
