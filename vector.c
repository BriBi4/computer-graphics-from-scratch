#include "vector.h"

#include <math.h>

struct Vector addVectors(struct Vector v1, struct Vector v2) {
	struct Vector vectorSum = {
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};
	return vectorSum;
}

struct Vector subtractVectors(struct Vector v1, struct Vector v2) {
	struct Vector vectorDifference = {
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};
	return vectorDifference;
}

float dotProduct(struct Vector v1, struct Vector v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

struct Vector scaleVector(float k, struct Vector v) {
	struct Vector scaledVector = { k*v.x, k*v.y, k*v.z };
	return scaledVector;
}

float magnitude(struct Vector v) {
	return sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
}

struct Vector normalize(struct Vector v) {
	float m = magnitude(v);
	struct Vector normalizedVector = { v.x/m, v.y/m, v.z/m };
	return normalizedVector;
}

struct Vector multiplyMatrixVector(struct Matrix matrix, struct Vector vector) {
	float *matrixArrays[3] = { matrix.a, matrix.b, matrix.c };
	float vectorArray[3] = { vector.x, vector.y, vector.z };
	float result[3] = {0, 0, 0,};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i] += vectorArray[j]*matrixArrays[i][j];
		}
	}
	struct Vector resultVector = {result[0], result[1], result[2]};
	return resultVector;
}

