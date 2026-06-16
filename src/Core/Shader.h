#pragma once
#include <config.h>

#include "glm/fwd.hpp"

class Shader {
public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setMat4(const std::string& name, const glm::mat4& value);
private:
    unsigned int m_Id;
    int getLocation(const std::string& name);
};
