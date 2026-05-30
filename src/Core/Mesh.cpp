#include "Mesh.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

Mesh::Mesh(std::vector<Vertex>& vertices,
           std::vector<unsigned int>& indices)
    : m_VBO(vertices.data(), vertices.size() * sizeof(Vertex)),
      m_IBO(indices.data(), indices.size())
{
    m_VAO.bind();
    m_VBO.bind();
    m_IBO.bind();


    m_VAO.configure();
}

Mesh::~Mesh() {}

void Mesh::bind() const {
    m_VAO.bind();
    m_IBO.bind();
}

void Mesh::draw() const {
    glDrawElements(GL_TRIANGLES, m_IBO.get_count(), GL_UNSIGNED_INT, 0);
}
