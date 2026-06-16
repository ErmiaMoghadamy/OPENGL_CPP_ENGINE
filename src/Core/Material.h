#pragma once
#include "config.h"
#include "Shader.h"

class Material {
public:
    Material(std::shared_ptr<Shader> shader);
    ~Material() = default;

    void Bind() const;
    void Unbind() const;

    std::shared_ptr<Shader> GetShader() const { return m_shader; }

private:
    std::shared_ptr<Shader> m_shader;
};
