#pragma once

#include <vector>

#include "Layer.h"

namespace Smedja {

class LayerStack {
public:
    LayerStack();
    ~LayerStack();

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);


    std::vector<Layer *>::iterator begin() {
        return m_layerVec.begin();
    }
    std::vector<Layer *>::iterator end() {
        return m_layerVec.end();
    }

private:
    std::vector<Layer *> m_layerVec;
    std::vector<Layer *>::iterator m_insertionIter;
};

} // namespace Smedja
