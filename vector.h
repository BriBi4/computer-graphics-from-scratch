#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

struct Vector {
	float x;
	float y;
	float z;
};

struct Vector addVectors(struct Vector v1, struct Vector v2);
struct Vector subtractVectors(struct Vector v1, struct Vector v2);
float dotProduct(struct Vector v1, struct Vector v2);
struct Vector scaleVector(float k, struct Vector v);
float magnitude(struct Vector v);
struct Vector normalize(struct Vector v);

#endif
