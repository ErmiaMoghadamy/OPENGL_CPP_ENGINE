#pragma once
#include "Entity.h"

class Lamp : public Entity {
public:
    Lamp();
    virtual ~Lamp() = default;

    void Draw(const Camera& camera);

    std::unique_ptr<Shader> m_lampShader;
};