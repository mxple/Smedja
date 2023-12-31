#pragma once

#include "Events/Event.h"
#include "pch.h"

namespace Smedja {

class Layer {
public:
    Layer(const std::string &name = "Layer");
    virtual ~Layer();

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onEvent(Event &e) {}

    inline const std::string &getName() const {
        return m_debugName;
    }

protected:
    std::string m_debugName;
};

} // namespace Smedja
