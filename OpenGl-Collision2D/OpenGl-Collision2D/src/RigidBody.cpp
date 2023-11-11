#include "RigidBody.h"
#include <iostream>

#include "Utils.h"
using namespace glm;
RigidBody::RigidBody(Transform* rbTransform)  
{
    this->rbTransform = rbTransform;
    this->mass = rbTransform->getScale().x / 1.0f;
    this->acceleration = vec2(force / mass);
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

float RigidBody::getMass() const
{
    return mass;
}

void RigidBody::updatePhysics() {
    vec3 translation = vec3(this->direction.x * this->acceleration.x, this->direction.y * this->acceleration.y, 0);
    rbTransform->addTranslation(translation);
}
