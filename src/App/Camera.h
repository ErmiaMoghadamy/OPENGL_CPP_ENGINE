#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

class Camera {
public:
    Camera(float);

    void updateView();
    void updateProjection();

    void updateAspect(float);
    void updateFov(float);

    void RotateMouse(float dx, float dy);
    void MoveForward(float);
    void MoveRight(float);
    void MoveUp(float);

    glm::vec3 position;
    glm::vec3 target;

    glm::mat4 view;
    glm::mat4 projection;

    float yaw;
    float pitch;
    float lookDist;
    float sensitivity;

    float fov;
    float nearPlane;
    float farPlane;
    float aspect;
};
