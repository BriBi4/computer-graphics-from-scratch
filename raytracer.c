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

	for (int i = 0; i < sizeof(SPHERES) / sizeof(struct Sphere); i++) {
		//printf("%d: ", i);
		float *distances = intersectRaySphere(origin, direction, SPHERES[i]);
		//printf("%f, %f\n", distances[0], distances[1]);
		if (distances[0] > minDist && distances[0] < maxDist && distances[0] < closestDist) {
			closestDist = distances[0];
			closestSphere = (struct Sphere*)&SPHERES[i];
		}
		if (distances[1] > minDist && distances[1] < maxDist && distances[1] < closestDist) {
			closestDist = distances[1];
			closestSphere = (struct Sphere*)&SPHERES[i];
		}
	}

	if (closestSphere == NULL)
		return BACKGROUND_COLOR;
	//printf("%d, %d, %d\n", (*closestSphere).color.r, (*closestSphere).color.g, (*closestSphere).color.b);
	return (*closestSphere).color;
}

float *intersectRaySphere(struct Vector origin, struct Vector direction, struct Sphere sphere) {
	float r = sphere.radius;
	struct Vector CO = subtractVectors(origin, sphere.center);

	float a = dotProduct(direction, direction);
	float b = 2 * dotProduct(CO, direction);
	float c = dotProduct(CO, CO) - (r*r);

	float discriminant = (b*b) - (4*a*c);
	//printf("discriminant: %f\n", discriminant);
	if (discriminant < 0) {
		static float distances[2] = {FLT_MAX, FLT_MAX};
		return distances;
	}

	static float distances[2];
	distances[0] = (-b + sqrt(discriminant)) / (2*a);
	distances[1] = (-b - sqrt(discriminant)) / (2*a);
	return distances;
}
