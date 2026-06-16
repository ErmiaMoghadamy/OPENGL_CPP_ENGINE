#pragma once
#include <string>


class Texture {
public:
    Texture(const std::string &filePath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind();

    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }
private:
    unsigned int m_id;

    std::string m_file_path;
    unsigned char* m_local_buffer;
    int m_width, m_height, m_bpp;
};
