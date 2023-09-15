#pragma once
#include "Transform.h"
#include "RigidBody.h"

class Particle
{
public:
	Particle();

	Transform transform;
	RigidBody rigidBody = RigidBody(&transform);

	vec4 color;
	float* getVertices();
	unsigned int* getIndices();
	unsigned int getVerticesSize();
	unsigned int getIndicesSize();
	vec4 getColor();
private:
	void createVertices();
	const float radius = 20.0f;
	const int numSegments = 50;
	const int numVertices = numSegments + 1;
	const int numIndices = numSegments * 3;

	float* particleVertices;
	unsigned int* particleIndices;
};