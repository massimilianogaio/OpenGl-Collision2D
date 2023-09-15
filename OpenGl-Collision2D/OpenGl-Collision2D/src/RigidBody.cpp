#include "RigidBody.h"
#include <iostream>

#include "Utils.h"
using namespace glm;
RigidBody::RigidBody(Transform* rbTransform) : acceleration(vec2(.1f))  
{
    this->rbTransform = rbTransform;
    this->direction = vec2(GetRandomNumber(-1.0, 1.0f), GetRandomNumber(-1.0, 1.0f));
}

void RigidBody::setAcceleration(const vec2& velocity) {
    this->acceleration = velocity;
}

vec2 RigidBody::getAcceleration() const {
    return acceleration;
}

void RigidBody::setDirection(const vec2& direction) {
    this->direction = direction;
}

vec2 RigidBody::getDirection() const {
    return direction;
}

void RigidBody::updatePhysics() {
    vec3 translation = vec3(direction.x * acceleration.x, direction.y * acceleration.y, 0);
    rbTransform->addTranslation(translation);
}
