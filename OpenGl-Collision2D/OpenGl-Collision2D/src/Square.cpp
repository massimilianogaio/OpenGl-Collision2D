#include "Square.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "Utils.h"

Square::Square()
{
    transform.setScale(vec3(GetRandomNumber(1.0f, 2.0f)));
    color = vec4(GetRandomNumber(0.0f, 1.0f), GetRandomNumber(0.0f, 1.0f), GetRandomNumber(0.0f, 1.0f), 1.0f);
    createVertices();

    rigidBody = new RigidBody(&transform);
}

void Square::createVertices()
{
    unsigned int indicesSquare[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    squareIndices = new unsigned int[6];
    for (int i = 0; i < 6; i++)
    {
        squareIndices[i] = indicesSquare[i];

    }
    squareVertices = new float[6 * 2];
    float halfWidth = 20.0f;
    float halfWidthNegative = halfWidth * -1.0f;
    float verticesSquare[] = {
        halfWidth,  halfWidth, 0.0f,  // top right
         halfWidth, halfWidthNegative, 0.0f,  // bottom right
        halfWidthNegative, halfWidthNegative, 0.0f,  // bottom left
        halfWidthNegative,  halfWidth, 0.0f   // top left 
    };

    for (int i = 0; i < 6 * 2; i++)
    {
        squareVertices[i] = verticesSquare[i];
    }

}
unsigned int* Square::getIndices() { return squareIndices; }
float* Square::getVertices() { return squareVertices; }

unsigned int Square::getVerticesSize()
{
    return sizeof(float) * 6 * 2;
}
unsigned int Square::getIndicesSize()
{
    return sizeof(unsigned int) * 6;
}

vec4 Square::getColor()
{
    return color;
}
