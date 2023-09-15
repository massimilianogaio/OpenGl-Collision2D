#include "Transform.h"
#include <iostream>
using namespace glm;

Transform::Transform()
    : position(vec3(0.0f)), rotation(vec3(0.0f)), scale(vec3(1.0f)), transformMatrix(mat4(1.0f)) {
    updateTransform();
}

void Transform::setPosition(const vec3& position) {
    this->position = position;
    this->transformMatrix = translate(this->transformMatrix, position);
}
void Transform::addTranslation(const vec3& translation) {
    
    this->position += translation;
    this->transformMatrix = translate(this->transformMatrix, position);
}

void Transform::setRotation(const vec3& rotation) {
    this->rotation = rotation;
    this->transformMatrix = rotate(this->transformMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    this->transformMatrix = rotate(this->transformMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    this->transformMatrix = rotate(this->transformMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
}

void Transform::setScale(const vec3& scale) {
    this->scale = scale;
    this->transformMatrix = glm::scale(this->transformMatrix, scale);
}

vec3 Transform::getPosition() const {
    return position;
}

vec3 Transform::getRotation() const {
    return rotation;
}

vec3 Transform::getScale() const {
    return scale;
}

void Transform::updateTransform() {
    this->transformMatrix = mat4(1.0f);
    this->transformMatrix = translate(this->transformMatrix, position);
    this->transformMatrix = rotate(this->transformMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    this->transformMatrix = rotate(this->transformMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    this->transformMatrix = rotate(this->transformMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
    this->transformMatrix = glm::scale(this->transformMatrix, scale);
}

mat4 Transform::getTransformMatrix() {
    updateTransform();
    return transformMatrix;
}
