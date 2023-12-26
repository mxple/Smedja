#pragma once

#include "Event.h"

namespace Smedja {

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {}

    EVENT_CLASS_TYPE(WindowClose)

    std::string toString() const override {
        return "WindowCloseEvent";
    }
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_width(width), m_height(height) {}

    EVENT_CLASS_TYPE(WindowResize)

    inline unsigned int getWidth() const {
        return m_width;
    }
    inline unsigned int getHeight() const {
        return m_height;
    }

    std::string toString() const override {
        return "WindowResizeEvent: " + std::to_string(m_width) + ", " +
               std::to_string(m_height);
    }

private:
    unsigned int m_width, m_height;
};

// class WindowFocusEvent : public Event {};
// class WindowLostFocusEvent : public Event {};
// class WindowMovedEvent : public Event {};
} // namespace Smedja
