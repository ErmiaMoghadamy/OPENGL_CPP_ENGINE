#include "Shader.h"
#include "config.h"

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

