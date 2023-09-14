#pragma once
class Particle
{
public:
	void createVertices();
	float* getVertices();
	unsigned int* getIndices();
	unsigned int getVerticesSize();
	unsigned int getIndicesSize();
private:
	const float radius = 0.5f;
	const int numSegments = 50;
	const int numVertices = numSegments + 1;
	const int numIndices = numSegments * 3;

	float* particleVertices;
	unsigned int* particleIndices;
};