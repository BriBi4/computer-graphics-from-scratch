#include "vector.h"

struct Vector subtractVectors(struct Vector v1, struct Vector v2) {
	struct Vector vectorDifference = {
		(v1.x - v2.x),
		(v1.y - v2.y),
		(v1.z - v2.z)
	};
	return vectorDifference;
}

float dotProduct(struct Vector v1, struct Vector v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}
