#include "Scene.h"
#include "config.h"
#include "Renderer.h"

std::vector<Vertex> vertices = {
    {
        {-0.5f, -0.5f, 0.0f}, // position
        {1.0f, 0.0f, 0.0f, 1.0f},   // color (red)
        {0.0f, 0.0f},         // texCoord
        {0.0f, 0.0f, 0.0f}    // normal
    },
    {
            { 0.5f, -0.5f, 0.0f},
            {0.0f, 1.0f, 0.0f, 1.0f},   // green
            {0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f}
    },
    {
            { 0.0f,  0.5f, 0.0f},
            {0.0f, 0.0f, 1.0f, 1.0f},   // blue
            {0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f}
    }
};

std::vector<unsigned int> indices = {
    0, 1, 2
};

const char* vertexShader = R"gsl(
#version 330 core

layout (location=0) in vec3 in_position;
layout (location=1) in vec4 in_color;
layout (location=2) in vec2 texture_coord;
layout (location=3) in vec3 normal;

out vec4 v_color;

void main() {
    gl_Position = vec4(in_position, 1.0);
    v_color = in_color;
}
)gsl";

const char* fragmentShader = R"gsl(
#version 330 core

in vec4 v_color;
out vec4 out_color;

void main() {
    out_color = v_color;
}

)gsl";


Scene::Scene(): m_ball_mesh(nullptr) {
}

Scene::~Scene() = default;

void Scene::boostrap() {
    m_ball_shader = std::make_unique<Shader>(vertexShader, fragmentShader);
    m_ball_mesh = std::make_unique<Mesh>(vertices, indices);
}

void Scene::run() {

    Renderer::clear();
    m_ball_shader->bind();
    Renderer::draw(m_ball_mesh.get());
}
