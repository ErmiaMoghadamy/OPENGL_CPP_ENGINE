#include "Entity.h"

#include "App/Camera.h"
#include "Core/Shader.h"

Entity::Entity() : m_transform(), m_mesh(nullptr) {
}

Entity::Entity(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_transform(), m_mesh(std::make_unique<Mesh>(vertices, indices)) {
}

void Entity::Draw(const Camera& camera, Shader& shader) {
    shader.bind();

    shader.setMat4("u_model", m_transform.getModel());
    shader.setMat4("u_view", camera.view);
    shader.setMat4("u_projection", camera.projection);

    m_mesh->bind();
    m_mesh->draw();
}
