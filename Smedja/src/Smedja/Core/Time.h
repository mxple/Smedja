#pragma once

namespace Smedja {

class TimeStep {
public:
    TimeStep(float time) : m_time(time) {} 

    operator float() const { return m_time; }

    float seconds() const { return m_time; }
    float milliseconds() const { return m_time * 1000.0f; }

private:
    float m_time;
};

}
