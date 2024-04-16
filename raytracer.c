#include <stdio.h>
#include <float.h>
#include <math.h>

#include "canvas.h"
#include "scene.h"
#include "vector.h"
#include "color.h"

void paintCanvas();
struct Vector canvasToViewport(int canvasX, int canvasY);
struct Color traceRay(struct Vector origin, struct Vector direction, float minDist, float maxDist);
float *intersectRaySphere(struct Vector origin, struct Vector direction, struct Sphere sphere);

float computeLighting(struct Vector point, struct Vector normal);

int main(int argc, char *argv[]) {
	setupCanvas();
	paintCanvas();
	displayCanvas();
	while (1) {
		if (windowClosed())
			break;
	}
	cleanupCanvas();
	return 0;
}

void paintCanvas() {
	struct Vector origin = CAMERA_POSITION;
	for (int x = -CANVAS_WIDTH/2; x < CANVAS_WIDTH/2; x++) {
		for (int y = -CANVAS_HEIGHT/2; y < CANVAS_HEIGHT/2; y++) {
			struct Vector D = canvasToViewport(x, y);
			struct Color color = traceRay(origin, D, 1, FLT_MAX);
			putPixel(x, y, color);
		}
	}
}

struct Vector canvasToViewport(int canvasX, int canvasY) {
	struct Vector viewportPoint = {
		canvasX * (VIEWPORT_WIDTH/CANVAS_WIDTH),
		canvasY * (VIEWPORT_HEIGHT/CANVAS_HEIGHT),
		VIEWPORT_DISTANCE
	};
	return viewportPoint;
}

struct Color traceRay(struct Vector origin, struct Vector direction, float minDist, float maxDist) {
	float closestDist = FLT_MAX;
	struct Sphere *closestSphere = NULL;

	for (int i = 0; i < sizeof(SPHERES)/sizeof(struct Sphere); i++) {
		float *distances = intersectRaySphere(origin, direction, SPHERES[i]);
		if (distances[0] > minDist && distances[0] < maxDist && distances[0] < closestDist) {
			closestDist = distances[0];
			closestSphere = (struct Sphere*)&SPHERES[i];
		}
		if (distances[1] > minDist && distances[1] < maxDist && distances[1] < closestDist) {
			closestDist = distances[1];
			closestSphere = (struct Sphere*)&SPHERES[i];
		}
	}

	if (closestSphere == NULL) {
		return BACKGROUND_COLOR;
	}
	
	struct Vector point = addVectors( origin, scaleVector(closestDist, direction) );
	struct Vector normal = subtractVectors(point, closestSphere->center);
	normal = normalize(normal);
	return modifyColorIntensity(computeLighting(point, normal), closestSphere->color);
}

float *intersectRaySphere(struct Vector origin, struct Vector direction, struct Sphere sphere) {
	float r = sphere.radius;
	struct Vector CO = subtractVectors(origin, sphere.center);

	float a = dotProduct(direction, direction);
	float b = 2 * dotProduct(CO, direction);
	float c = dotProduct(CO, CO) - (r*r);

	float discriminant = (b*b) - (4*a*c);
	if (discriminant < 0) {
		static float distances[2] = {FLT_MAX, FLT_MAX};
		return distances;
	}

	static float distances[2];
	distances[0] = (-b + sqrt(discriminant)) / (2*a);
	distances[1] = (-b - sqrt(discriminant)) / (2*a);
	return distances;
}

float computeLighting(struct Vector point, struct Vector normal) {
	float intensity = 0;
	for (int i = 0; i < sizeof(LIGHTS)/sizeof(struct Light); i++) {
		if (LIGHTS[i].type == LIGHT_AMBIENT) {
			intensity += LIGHTS[i].intensity;
		} else {
			struct Vector light_direction;
			if (LIGHTS[i].type == LIGHT_POINT) {
				light_direction = subtractVectors(LIGHTS[i].posOrDir, point);
			} else {
				light_direction = LIGHTS[i].posOrDir;
			}
			float normalDotLight = dotProduct(normal, light_direction);
			if (normalDotLight > 0) {
				intensity += LIGHTS[i].intensity * normalDotLight / ( magnitude(normal)*magnitude(light_direction) );
			}
		}
	}
	return intensity;
}
