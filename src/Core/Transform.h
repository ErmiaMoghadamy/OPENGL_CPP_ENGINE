#pragma once
#include "config.h"

class Transform {
public:
    Transform();

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 getModel() const;

    void translate(const glm::vec3& delta);
    void rotate(const glm::vec3& delta);
    void setScale(const glm::vec3& newScale);

private:
    mutable bool dirty;
    mutable glm::mat4 cachedMatrix;

    void updateMatrix() const;
};