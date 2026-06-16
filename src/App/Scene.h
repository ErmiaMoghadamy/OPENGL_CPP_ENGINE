#pragma once
#include "config.h"
#include "Camera.h"
#include "Core/Mesh.h"
#include "Core/Shader.h"
#include "Core/Texture.h"
#include "Entities/Ball.h"
#include "Entities/Floor.h"
#include "Entities/Lamp.h"

class Scene {
public:
    Scene(float);
    ~Scene();

    void updateAspect(float);
    void boostrap();
    void run();

    Camera m_camera;
private:
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Floor> m_floor;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Texture> m_floor_texture;
    std::unique_ptr<Texture> m_ball_texture;
    std::unique_ptr<Lamp> m_lamp;
};
