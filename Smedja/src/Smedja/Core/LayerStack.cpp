#include "LayerStack.h"

namespace Smedja {

LayerStack::LayerStack() {
    m_insertionIter = m_layerVec.begin();
}

LayerStack::~LayerStack() {
    for (Layer *layer : m_layerVec) {
        delete layer;
    }
}

void LayerStack::pushLayer(Layer *layer) {
    m_layerVec.emplace(m_insertionIter++, layer);
    layer->onAttach();
}

void LayerStack::pushOverlay(Layer *overlay) {
    m_layerVec.emplace_back(overlay);
    overlay->onAttach();
}

void LayerStack::popLayer(Layer *layer) {
    auto toDelete = std::find(m_layerVec.begin(), m_layerVec.end(), layer);
    if (toDelete != m_layerVec.end()) {
        m_layerVec.erase(toDelete);
        (*toDelete)->onDetach();
        m_insertionIter--;
        return;
    }
    SD_CORE_WARN("Attempted to delete non-existent layer");
}

void LayerStack::popOverlay(Layer *overlay) {
    auto toDelete = std::find(m_layerVec.begin(), m_layerVec.end(), overlay);
    if (toDelete != m_layerVec.end()) {
        m_layerVec.erase(toDelete);
        (*toDelete)->onDetach();
        return;
    }
    SD_CORE_WARN("Attempted to delete non-existent overlay");
}

} // namespace Smedja
