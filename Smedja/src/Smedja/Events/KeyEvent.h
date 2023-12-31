#pragma once

#include "Event.h"

namespace Smedja {

class KeyEvent : public Event {
public:
    inline int getKeyCode() const {
        return m_keyCode;
    }

protected:
    KeyEvent(int keyCode) : m_keyCode(keyCode) {}

    int m_keyCode; // TODO: Make this an enum
    
    // idk if these will stay
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keyCode) : KeyEvent(keyCode) {}

    EVENT_CLASS_TYPE(KeyPressed)

    std::string toString() const override {
        return "KeyPressedEvent: " + std::to_string(m_keyCode); // TODO: enum
    }
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

    EVENT_CLASS_TYPE(KeyReleased)

    std::string toString() const override {
        return "KeyReleasedEvent: " + std::to_string(m_keyCode); // TODO: enum
    }
};

// Not sure if key repeat event is needed.
// Might be better to handle via game logic.

} // namespace Smedja
