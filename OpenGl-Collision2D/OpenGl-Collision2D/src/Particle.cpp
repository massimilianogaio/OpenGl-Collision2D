#include "Particle.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "Utils.h"

Particle::Particle()
{
    transform.setScale(vec3(GetRandomNumber(1.0f, 2.0f)));
    color = vec4(GetRandomNumber(0.0f, 1.0f), GetRandomNumber(0.0f, 1.0f), GetRandomNumber(0.0f, 1.0f), 1.0f);
    createVertices();

    rigidBody = new RigidBody(&transform);
}

void Particle::createVertices()
{
	particleVertices = new float[numVertices * 2];
	particleIndices = new unsigned int[numIndices];

    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * 3.14f * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        particleVertices[i * 2] = x;
        particleVertices[i * 2 + 1] = y;

        // Add indices for the triangle fan
        if (i > 0) {
            particleIndices[(i - 1) * 3] = 0;
            particleIndices[(i - 1) * 3 + 1] = i;
            particleIndices[(i - 1) * 3 + 2] = i - 1;
        }
        
    }
}
unsigned int* Particle::getIndices() { return particleIndices; }
float* Particle::getVertices() { return particleVertices; }

unsigned int Particle::getVerticesSize()
{
    return sizeof(float) * numVertices * 2;
}
unsigned int Particle::getIndicesSize()
{
    return sizeof(unsigned int) * numVertices * 3;
}
vec4 Particle::getColor()
{
    return color;
}
EShapeType Particle::GetShapeType()
{
    return EShapeType::Circle;
}
float Particle::getScaledSize()
{
    return radius * transform.getScale().x;
}
bool Particle::IsPositionInsideShape(vec3 pos)
{
    float distance = glm::distance(pos, transform.getPosition());
    return distance < getScaledSize();
}