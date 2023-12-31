#pragma once

#include "Smedja/Layer.h"
#include "Smedja/Events/Event.h"

namespace Smedja {

class ImGuiLayer : public Layer { 
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void onAttach();
    virtual void onDetach();

    virtual void onUpdate();
    virtual void onEvent(Event& e);

private:

};

}
