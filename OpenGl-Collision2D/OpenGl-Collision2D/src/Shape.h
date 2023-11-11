#pragma once
#include "Transform.h"
#include "RigidBody.h"

enum EShapeType {
    Quadrilateral,
    Circle
};

class Shape {
public:
    virtual ~Shape() {}

    Transform transform;
    RigidBody* rigidBody;
    
    virtual float* getVertices() = 0;
    virtual unsigned int* getIndices() = 0;
    virtual unsigned int getVerticesSize() = 0;
    virtual unsigned int getIndicesSize() = 0;
    virtual vec4 getColor() = 0;
    virtual EShapeType GetShapeType() = 0;

protected:
    vec4 color;

    virtual void createVertices() = 0;
};