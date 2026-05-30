#pragma once
#include <config.h>

class Shader {
public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~Shader();

    void bind() const;
    void unbind() const;
private:
    unsigned int m_Id;
};
