#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/constants.hpp"

namespace {
    constexpr float INIT_FOV  = 0.98f;
    constexpr float INIT_NEAR = 0.01f;
    constexpr float INIT_FAR  = 100.0f;

    const glm::vec3 UP(0.0f, 1.0, 0.0f);
}

Camera::Camera(float aspectRatio)
: position(0.0f, 0.0, 5.0f),
      yaw(-glm::half_pi<float>()),
      pitch(0.0f),
      lookDist(1.0f),
      sensitivity(0.002f),
      fov(INIT_FOV),
      nearPlane(INIT_NEAR),
      farPlane(INIT_FAR),
      aspect(aspectRatio) {

    target = position + glm::vec3(0.0f, 0.0f, 0.0f);

    updateView();
    updateProjection();
}

void Camera::updateProjection() {
    this->projection = glm::perspective(
        fov,
        aspect,
        nearPlane,
        farPlane
    );
}


void Camera::updateView()
{
    const float cy = std::cos(this->yaw);
    const float sy = std::sin(this->yaw);
    const float cp = std::cos(this->pitch);
    const float sp = std::sin(this->pitch);

    glm::vec3 forward(
        cy * cp,
        sp,
        sy * cp
    );

    forward = glm::normalize(forward);

    this->target = this->position + forward * this->lookDist;

    this->view = glm::lookAt(
        this->position,
        this->target,
        UP
    );
}

void Camera::updateAspect(float aspectRatio) {
    this->aspect = aspectRatio;
    updateProjection();
}

void Camera::updateFov(float newFov) {
    this->fov = newFov;
    updateProjection();
}

void Camera::RotateMouse(float dx, float dy) {
    this->yaw += dx * this->sensitivity;
    this->pitch += dy * this->sensitivity;

    const float limit = glm::radians(89.0f);
    this->pitch = std::clamp(this->pitch, -limit, limit);

    this->updateView();
}


void Camera::MoveForward(float amount) {
    glm::vec3 forward = glm::normalize(this->target - this->position);
    glm::vec3 right = glm::normalize(glm::cross(forward, UP));

    glm::vec3 forward_level = glm::normalize(glm::cross(UP, right));

    glm::vec3 movement = forward_level * (-amount);

    this->position += movement;
    this->target += movement;

    updateView();
}

void Camera::MoveRight(float amount) {
    glm::vec3 forward = glm::normalize(this->target - this->position);
    glm::vec3 right = glm::normalize(glm::cross(forward, UP));

    glm::vec3 movement = right * amount;

    this->position += movement;
    this->target += movement;

    this->updateView();
}

void Camera::MoveUp(float amount) {
    glm::vec3 movement = UP * amount;

    this->position += movement;
    this->target += movement;

    this->updateView();
}