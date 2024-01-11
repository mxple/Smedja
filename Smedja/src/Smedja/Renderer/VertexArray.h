#pragma once

#include "Buffer.h"

namespace Smedja { 

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addVertexBuffer(std::shared_ptr<VertexBuffer> &VBO);
    void setIndexBuffer(std::shared_ptr<IndexBuffer> &EBO);

    std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers();
    std::shared_ptr<IndexBuffer> &getIndexBuffer();

    void bind();
    void unbind();

private:
    unsigned int m_ID;
    unsigned int m_layoutLocation = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_VBOs;
    std::shared_ptr<IndexBuffer> m_EBO;
};

}
