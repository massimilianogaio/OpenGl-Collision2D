#pragma once
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Transform {
public:
    Transform();

    void addTranslation(const vec3& position);
    void setPosition(const vec3& position);
    void setRotation(const vec3& rotation);
    void setScale(const vec3& scale);

    vec3 getPosition() const;
    vec3 getRotation() const;
    vec3 getScale() const;

    void updateTransform();
    mat4 getTransformMatrix();

private:
    vec3 position;
    vec3 rotation;
    vec3 scale;
    mat4 transformMatrix;
};