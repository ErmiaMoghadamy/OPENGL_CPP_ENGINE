#pragma once
#include "config.h"
#include "Core/Mesh.h"
#include "Core/Shader.h"

class Scene {
public:
    Scene();
    ~Scene();

    void boostrap();
    void run();

private:
    std::unique_ptr<Mesh> m_ball_mesh;
    std::unique_ptr<Shader> m_ball_shader;
};
