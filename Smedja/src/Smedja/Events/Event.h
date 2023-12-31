#pragma once

#include "pch.h"

namespace Smedja {

enum class EventType {
    Empty = 0,

    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,

    KeyPressed,
    KeyReleased
};

#define EVENT_CLASS_TYPE(type)                                                 \
    static EventType getStaticType() { return EventType::type; }               \
    virtual EventType getEventType() const override { return getStaticType(); }

// Event is a base or abstract class for all event types
class Event {
    friend class EventDispatcher; // Allows EventDispatcher to set m_handled
public:
    virtual ~Event() = default;

    virtual EventType getEventType() const = 0;
    virtual std::string toString() const = 0;

    inline bool isHandled() const {
        return m_handled;
    }

private:
    bool m_handled = false;
};

class EventDispatcher {
    template <typename E>
    using EventFn = std::function<bool(E &)>;

public:
    EventDispatcher(Event &e) : m_event(e) {}

    template <typename E>
    bool dispatch(std::function<bool(E &)> func) {
        if (m_event.getEventType() == E::getStaticType()) {
            // Casts m_event to template type E, then calls func on it
            m_event.m_handled = func(*(E *)&m_event);
            return true;
        }
        // SD_WARN("EventDispatcher: Event type mismatch");
        return false;
    }

private:
    Event &m_event; // Referenece allows virtual function calls
};

// Format for logging
inline std::ostream &operator<<(std::ostream &os, const Event &e) {
    return os << e.toString();
}

} // namespace Smedja
