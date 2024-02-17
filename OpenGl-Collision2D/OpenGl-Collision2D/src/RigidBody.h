#pragma once
#include <glm/glm.hpp>
#include "Transform.h"
using namespace glm;

class RigidBody {
public:
    RigidBody(Transform* rbTransform);

    void setDirection(const vec2& direction);
    vec2 getDirection() const;
    float getMass() const;
    void setAcceleration(const vec2& velocity);
    vec2 getAcceleration() const;
    void updatePhysics(float deltaTime);
private:
    float force = .3f;
    float mass;
    vec2 direction;
    vec2 acceleration;
    Transform* rbTransform;
};
