#pragma once 

#include <glad/glad.h>

#include "pch.h"

namespace Smedja {

enum class ShaderDataType {
    Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static unsigned int getShaderTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;   // is this right?
        }
        SD_CORE_ASSERT(false, "Shader data type not recognized                 \
                       (how is this even possible?)");
        return 0;
}

// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
// Specifies how data is laid out in a vertex buffer
// Each element corresponds to a gl buffer attrib ptr
struct BufferElement {
    unsigned int m_componentCount;
    ShaderDataType m_type;  // component count and gl type from here
    GLenum m_glType;
    bool m_normalized;
    // stride handled by layout class
    unsigned int m_offset;  // m_offset calculated by layout class
    
    BufferElement() = default;

    BufferElement(ShaderDataType type, bool normalized = true) :
        m_componentCount(calcComponentCount(type)), m_type(type),
        m_glType(getGLType(type)), m_normalized(normalized) {}

    GLenum getGLType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:  return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:  return GL_INT;
            case ShaderDataType::Bool:  return GL_BOOL;
        }
        SD_CORE_ASSERT(false, "Shader data type not recognized                 \
                       (how is this even possible?)");
        return 0;
    }

    unsigned int calcComponentCount(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 3;
            case ShaderDataType::Mat4:      return 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::Bool:      return 1;
        }

        SD_CORE_ASSERT(false, "Shader data type not recognized                 \
                       (how is this even possible?)");
        return 0;
    }
};

// Basically a utility wrapper around std::vector<BufferElement>
class BufferLayout {
public:
    BufferLayout();

    BufferLayout(std::initializer_list<BufferElement> elements) 
        : m_elements(elements) {
        calcStrideAndOffsets();
    }

    // TODO check this for memory safety
    void push_back(BufferElement &e) {
        m_elements.push_back(e);
        calcStrideAndOffsets();
    }

    void clear() {
        m_elements.clear();
        m_stride = 0;
    }

    bool empty() const {
        return m_elements.empty();
    }

	const std::vector<BufferElement>& GetElements() const {
        return m_elements;
    }

    std::vector<BufferElement>::iterator begin() {
        return m_elements.begin();
    }
    std::vector<BufferElement>::iterator end() {
        return m_elements.end();
    }
    std::vector<BufferElement>::const_iterator begin() const {
        return m_elements.begin();
    }
    std::vector<BufferElement>::const_iterator end() const {
        return m_elements.end();
    }

private:
    void calcStrideAndOffsets() {
        m_stride = 0;
        unsigned int sz = 0;
        unsigned int offset = 0;
        for (BufferElement &e : m_elements) { 
            e.m_offset = offset;
            sz         = getShaderTypeSize(e.m_type);
            offset    += sz;
            m_stride  += sz;
        }
    }

    std::vector<BufferElement> m_elements;
    unsigned int m_stride;
};

} // namespace Smedja
