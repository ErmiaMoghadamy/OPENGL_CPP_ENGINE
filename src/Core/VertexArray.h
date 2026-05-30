#pragma once

class VertexArray {
    public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    void configure();

private:
    unsigned int m_Id;
};
