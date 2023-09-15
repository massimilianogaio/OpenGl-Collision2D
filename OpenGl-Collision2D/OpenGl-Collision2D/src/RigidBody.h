#pragma once
#include <glm/glm.hpp>
#include "Transform.h"

class RigidBody {
public:
    RigidBody(Transform* rbTransform, vec2 direction);

    void setDirection(const glm::vec2& direction);
    glm::vec2 getDirection() const;
    void setAcceleration(const glm::vec2& velocity);
    glm::vec2 getAcceleration() const;
    void update();
private:
    glm::vec2 direction;
    glm::vec2 acceleration;
    Transform* rbTransform;
};
