#pragma once

#include "Event.h"

namespace Smedja {

class CharTypedEvent : public Event {
public:
    CharTypedEvent(unsigned int codepoint) : m_codepoint(codepoint) {}

    EVENT_CLASS_TYPE(CharTyped)

    inline unsigned int getCodepoint() const {
        return m_codepoint;
    }

    std::string toString() const override {
        std::string s = "CharTypedEvent: ";
        s += static_cast<char>(m_codepoint);
        return s;
    }

private:
    unsigned int m_codepoint;
};

} // namespace Smedja
