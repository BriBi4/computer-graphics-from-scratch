#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

struct Vector {
	float x;
	float y;
	float z;
};

struct Vector subtractVectors(struct Vector v1, struct Vector v2);
float dotProduct(struct Vector v1, struct Vector v2);

#endif
