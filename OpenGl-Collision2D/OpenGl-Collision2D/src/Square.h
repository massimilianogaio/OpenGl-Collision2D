#pragma once
#include "Shape.h"

class Square : public Shape {
public:
	Square();

	float* getVertices() override;
	unsigned int* getIndices() override;
	unsigned int getVerticesSize() override;
	unsigned int getIndicesSize() override;
	vec4 getColor() override;
	EShapeType GetShapeType() override;
	bool IsPositionInsideShape(vec3 pos) override;
	float getScaledSize() override;
protected:
	void createVertices() override;
private:
	const float size = 20.0f;

	float* squareVertices;
	unsigned int* squareIndices;
};