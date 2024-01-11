#include "VertexArray.h"

namespace Smedja {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
}
VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_ID);
    // buffers should be handled by shared ptr
}

void VertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> &VBO) {
    glBindVertexArray(m_ID);
    VBO->bind();
    const BufferLayout &layout = VBO->getLayout();
    for (const BufferElement &e : layout) {
        switch (e.m_type) {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4: {
            SD_CORE_INFO("{}", m_layoutLocation);
            glEnableVertexAttribArray(m_layoutLocation);
            glVertexAttribPointer(m_layoutLocation, e.m_componentCount,
                                  e.m_glType, e.m_normalized,
                                  layout.getStride(), e.m_offset);
            m_layoutLocation++;
            break;
        }
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
        case ShaderDataType::Bool: {
            glEnableVertexAttribArray(m_layoutLocation);
            glVertexAttribIPointer(m_layoutLocation, e.m_componentCount,
                                   e.m_glType, layout.getStride(), e.m_offset);
            m_layoutLocation++;
            break;
        }
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4: {
            for (uint8_t i = 0; i < e.m_componentCount; i++) {
                glEnableVertexAttribArray(m_layoutLocation);
                // black magic
                glVertexAttribPointer(
                    m_layoutLocation, e.m_componentCount, e.m_glType,
                    e.m_normalized, layout.getStride(),
                    (const void *)(*(int *)e.m_offset +
                                   sizeof(float) * e.m_componentCount * i));
                glVertexAttribDivisor(m_layoutLocation, 1);
                m_layoutLocation++;
            }
            break;
        }
        default:
            SD_CORE_ASSERT(false, "Invalid shader data type!");
        }
    }
    m_VBOs.push_back(VBO);
}

void VertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> &EBO) {
    glBindVertexArray(m_ID);
    EBO->bind();
    m_EBO = EBO;
}

std::vector<std::shared_ptr<VertexBuffer>> &VertexArray::getVertexBuffers() {
    return m_VBOs;
}

std::shared_ptr<IndexBuffer> &VertexArray::getIndexBuffer() {
    return m_EBO;
}

void VertexArray::bind() {
    glBindVertexArray(m_ID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

} // namespace Smedja
