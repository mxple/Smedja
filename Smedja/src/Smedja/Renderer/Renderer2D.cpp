#include "Renderer2D.h"

namespace Smedja {

void Renderer2D::init() {
    // Create index buffer and bind to VAO
    unsigned int *indices = new unsigned int[Renderer2D::maxIndicies];
    int offset = 0;
    for (int i = 0; i < Renderer2D::maxIndicies; i += 6) {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }

    std::shared_ptr<IndexBuffer> ibo =
        std::make_shared<IndexBuffer>(indices, Renderer2D::maxIndicies);
    Renderer2D::s_vao->setIndexBuffer(ibo);
}

} // namespace Smedja
