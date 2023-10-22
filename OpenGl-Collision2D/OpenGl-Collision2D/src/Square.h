#pragma once
#include "Transform.h"
#include "RigidBody.h"

class Square
{
public:
	Square();

	Transform transform;
	RigidBody* rigidBody;

	vec4 color;
	float* getVertices();
	unsigned int* getIndices();
	unsigned int getVerticesSize();
	unsigned int getIndicesSize();
	vec4 getColor();
private:
	void createVertices();
	const float size = 20.0f;

	float* squareVertices;
	unsigned int* squareIndices;
};