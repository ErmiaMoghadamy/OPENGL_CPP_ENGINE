#pragma once
#include "App/Camera.h"
#include "Core/Mesh.h"
#include "Core/Shader.h"
#include "Core/Transform.h"

class Entity {
public:
    Entity();
    Entity(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    virtual ~Entity() = default;

    void Draw(const Camera& camera, Shader& shader);

    Transform m_transform;
    std::unique_ptr<Mesh> m_mesh;
    std::unique_ptr<Mesh> m_shader;
};
