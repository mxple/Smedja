#pragma once

#include "Event.h"

namespace Smedja {

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

    inline float getX() const {
        return m_mouseX;
    }
    inline float getY() const {
        return m_mouseY;
    }

    EVENT_CLASS_TYPE(MouseMoved)

    std::string toString() const override {
        return "MouseMovedEvent: " + std::to_string(m_mouseX) + ", " +
               std::to_string(m_mouseY);
    }

private:
    float m_mouseX, m_mouseY;
};

class MouseButtonPressedEvent : public Event {
public:
    MouseButtonPressedEvent(int button) : m_button(button) {}

    inline int getButton() const {
        return m_button;
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)

    std::string toString() const override {
        return "MouseButtonPressedEvent: " + std::to_string(m_button); // TODO
    }

private:
    int m_button; // TODO: Maybe make this an enum
};

class MouseButtonReleasedEvent : public Event {
public:
    MouseButtonReleasedEvent(int button) : m_button(button) {}

    inline int getButton() const {
        return m_button;
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)

    std::string toString() const override {
        return "MouseButtonReleasedEvent: " + std::to_string(m_button); // TODO
    }

private:
    int m_button; // TODO: Maybe make this an enum
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_xOffset(xOffset), m_yOffset(yOffset) {}

    inline float getXOffset() const {
        return m_xOffset;
    }
    inline float getYOffset() const {
        return m_yOffset;
    }

    EVENT_CLASS_TYPE(MouseScrolled)

    std::string toString() const override {
        return "MouseScrolledEvent: (" + std::to_string(m_xOffset) + ", " +
               std::to_string(m_yOffset) + ")";
    }

private:
    float m_xOffset, m_yOffset;
};

} // namespace Smedja
