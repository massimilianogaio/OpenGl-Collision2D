#include "RigidBody.h"
#include <iostream>
using namespace glm;
RigidBody::RigidBody(Transform* rbTransform, vec2 direction) : acceleration(vec2(.05f))  
{
    this->rbTransform = rbTransform;
    this->direction = direction;
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

void RigidBody::update() {

    vec3 translation = vec3(direction.x * acceleration.x, direction.y * acceleration.y, 0);
    rbTransform->addTranslation(translation);
}
