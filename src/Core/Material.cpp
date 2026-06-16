#include "Material.h"

Material::Material(std::shared_ptr<Shader> shader): m_shader(shader) {
}

void Material::Bind() const {
    if (m_shader) {
        m_shader->bind();
    }
}

void Material::Unbind() const {
    if (m_shader) {
        m_shader->unbind();
    }
}
