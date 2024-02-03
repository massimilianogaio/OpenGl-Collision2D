#pragma once
#include "Shape.h";

class Particle : public Shape {
public:
    Particle();

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
    const float radius = 50.0f;
    const int numSegments = 50;
    const int numVertices = numSegments + 1;
    const int numIndices = numSegments * 3;

    float* particleVertices;
    unsigned int* particleIndices;
};





