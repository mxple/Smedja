#pragma once

#include "BufferUtils.h"

namespace Smedja {

class VertexBuffer {
public:
    VertexBuffer(float *vertices, unsigned int size);
    ~VertexBuffer();

    void setData(float *vertices, unsigned int size);

    void setLayout(BufferLayout &layout);
    BufferLayout &getLayout();

    void bind();
    void unbind();

private:
    unsigned int m_ID;
    BufferLayout m_layout;  // should this be optional?
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
