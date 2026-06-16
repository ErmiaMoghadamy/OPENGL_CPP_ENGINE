#include "Texture.h"
#include "std_image.h"
#include "config.h"

namespace {
    constexpr int RGBA = 4;
}

Texture::Texture(const std::string &filePath) : m_id(0) , m_file_path(filePath), m_local_buffer(nullptr), m_width(0), m_height(0), m_bpp(0) {
    stbi_set_flip_vertically_on_load(1);
    std::cout << "Loading texture from: " << filePath << std::endl;
    m_local_buffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bpp, RGBA);

    if (!m_local_buffer)
    {
        std::cerr << "Failed to load texture: "
                  << filePath << '\n'
                  << "Reason: " << stbi_failure_reason()
                  << std::endl;

        throw std::runtime_error("Texture loading failed");
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_local_buffer != nullptr) {
        stbi_image_free(m_local_buffer);
    }

}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
