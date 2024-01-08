#pragma once

namespace Smedja {

class VertexBuffer {
public:
    VertexBuffer(float *vertices, unsigned int size);
    ~VertexBuffer();

    void bind();
    void unbind();

private:
    unsigned int m_ID;
};

class IndexBuffer {
public:
    IndexBuffer(unsigned int *indices, unsigned int count);
    ~IndexBuffer();

    void bind();
    void unbind();

private:
    unsigned int m_ID;
    unsigned int m_count;
};

} // namespace Smedja
