#include <stdio.h>
#include <float.h>
#include <math.h>

#include "canvas.h"
#include "scene.h"
#include "vector.h"
#include "color.h"

struct Intersection {
	struct Sphere *sphere;
	float distance;
};

const int RECURSION_LIMIT = 1;

void paintCanvas();
struct Vector canvasToViewport(int canvasX, int canvasY);
struct Color traceRay(struct Vector origin, struct Vector direction, float minDist, float maxDist, int recursionDepth);
struct Intersection closestIntersection(struct Vector origin, struct Vector direction, float minDist, float maxDist);
float *intersectRaySphere(struct Vector origin, struct Vector direction, struct Sphere sphere);

float computeLighting(struct Vector point, struct Vector normal, struct Vector viewDirection, float specular);

struct Vector reflectRay(struct Vector ray, struct Vector normal);

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
			struct Vector direction = multiplyMatrixVector(CAMERA_ROTATION, canvasToViewport(x, y));
			struct Color color = traceRay(origin, direction, 1, FLT_MAX, RECURSION_LIMIT);
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

struct Color traceRay(struct Vector origin, struct Vector direction, float minDist, float maxDist, int recursionDepth) {
	struct Intersection intersection = closestIntersection(origin, direction, minDist, maxDist);
	struct Sphere *closestSphere = intersection.sphere;
	float closestDist = intersection.distance;

	if (closestSphere == NULL) {
		return BACKGROUND_COLOR;
	}

	// Compute local color
	struct Vector point = addVectors( origin, scaleVector(closestDist, direction) );
	struct Vector normal = subtractVectors(point, closestSphere->center);
	normal = normalize(normal);
	struct Color localColor = modifyColorIntensity(computeLighting(point, normal, scaleVector(-1, direction), closestSphere->specular), closestSphere->color);

	// If we hit the recursion limit or the object is not reflective, we're done
	float reflective = closestSphere->reflective;
	if (recursionDepth <= 0 || reflective <= 0) {
		return localColor;
	}

	// Compute the reflected color
	struct Vector reflectedDirection = reflectRay(scaleVector(-1, direction), normal);
	struct Color reflectedColor = traceRay(point, reflectedDirection, 0.1, FLT_MAX, recursionDepth-1);

	return addColors( modifyColorIntensity(1-reflective, localColor), modifyColorIntensity(reflective, reflectedColor) );
}

struct Intersection closestIntersection(struct Vector origin, struct Vector direction, float minDist, float maxDist) {
	float closestDist = FLT_MAX;
	struct Sphere *closestSphere = NULL;
	for (int i = 0; i < sizeof(SPHERES)/sizeof(struct Sphere); i++) {
		float *distances = intersectRaySphere(origin, direction, SPHERES[i]);
		if (distances[0] > minDist && distances[0] < maxDist && distances[0] < closestDist) {
			closestDist = distances[0];
			closestSphere = (struct Sphere*) &SPHERES[i];
		}
		if (distances[1] > minDist && distances[1] < maxDist && distances[1] < closestDist) {
			closestDist = distances[1];
			closestSphere = (struct Sphere*) &SPHERES[i];
		}
	}
	struct Intersection intersection = {closestSphere, closestDist};
	return intersection;
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

float computeLighting(struct Vector point, struct Vector normal, struct Vector viewDirection, float specular) {
	float intensity = 0;
	for (int i = 0; i < sizeof(LIGHTS)/sizeof(struct Light); i++) {
		if (LIGHTS[i].type == LIGHT_AMBIENT) {
			intensity += LIGHTS[i].intensity;
		} else {
			struct Vector lightDirection;
			float maxDist;
			if (LIGHTS[i].type == LIGHT_POINT) {
				lightDirection = subtractVectors(LIGHTS[i].posOrDir, point);
				maxDist = 1;
			} else {
				lightDirection = LIGHTS[i].posOrDir;
				maxDist = FLT_MAX;
			}

			// Shadow check
			struct Intersection shadowIntersection = closestIntersection(point, lightDirection, 0.1, maxDist);
			if (shadowIntersection.sphere != NULL) {
				continue;
			}

			// Diffuse
			float normalDotLight = dotProduct(normal, lightDirection);
			if (normalDotLight > 0) {
				intensity += LIGHTS[i].intensity * normalDotLight / ( magnitude(normal)*magnitude(lightDirection) );
			}

			// Specular
			if (specular != -1) {
				struct Vector reflectedLightDirection = reflectRay(lightDirection, normal);
				float reflectedLightDotView = dotProduct(reflectedLightDirection, viewDirection);
				if (reflectedLightDotView > 0) {
					intensity += LIGHTS[i].intensity * pow(reflectedLightDotView / (magnitude(reflectedLightDirection)*magnitude(viewDirection)), specular);
				}
			}
		}
	}
	return intensity;
}

struct Vector reflectRay(struct Vector ray, struct Vector normal) {
	return subtractVectors(scaleVector(2*dotProduct(normal, ray), normal), ray);
}
