#include "Transform.h"
#include "config.h"

Transform::Transform()
    : position(0.0f, 0.0f, 0.0f),
      rotation(0.0f, 0.0f, 0.0f),
      scale(1.0f, 1.0f, 1.0f),
      dirty(true),
      cachedMatrix(1.0f) {
}

void Transform::translate(const glm::vec3& delta) {
    position += delta;
    dirty = true;
}

void Transform::rotate(const glm::vec3& delta) {
    rotation += delta;
    dirty = true;
}

void Transform::setScale(const glm::vec3& newScale) {
    scale = newScale;
    dirty = true;
}

glm::mat4 Transform::getModel() const {
    if (dirty)
        updateMatrix();

    return cachedMatrix;
}

void Transform::updateMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));

    model = glm::scale(model, scale);

    cachedMatrix = model;
    dirty = false;
}