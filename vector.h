#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

struct Vector {
	float x;
	float y;
	float z;
};

struct Matrix {
	float a[3];
	float b[3];
	float c[3];
};

struct Vector addVectors(struct Vector v1, struct Vector v2);
struct Vector subtractVectors(struct Vector v1, struct Vector v2);
float dotProduct(struct Vector v1, struct Vector v2);
struct Vector scaleVector(float k, struct Vector v);
float magnitude(struct Vector v);
struct Vector normalize(struct Vector v);
struct Vector multiplyMatrixVector(struct Matrix matrix, struct Vector vector);

#endif
