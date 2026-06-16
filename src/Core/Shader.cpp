#include "Shader.h"
#include "config.h"
#include "glm/gtc/type_ptr.hpp"

unsigned int CompileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "Shader compilation failed: " << message << std::endl;
        return 0;
    }

    return shader;
}


Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int program = glCreateProgram();

    unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::cout << "Program linking failed: " << message << std::endl;
    }

    m_Id = program;
}

Shader::~Shader() {
    glDeleteProgram(m_Id);
}

void Shader::bind() const {
    glUseProgram(m_Id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

int Shader::getLocation(const std::string& name)
{
    return glGetUniformLocation(m_Id, name.c_str());
}

void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(getLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(getLocation(name), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3f(getLocation(name), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4f(getLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(
        getLocation(name),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    );
}