#pragma once

#include "pch.h"

namespace Smedja {

class Shader {
public:
    Shader();   // no arg constructor for when we pass in code directly
    Shader(std::string& vertPath, std::string& fragPath);
    ~Shader();

    // takes in source code for shaders and then compiles + links them
    void init(const char* vertSource, const char* fragSource);

    void bind();
    void unbind();

    // uniforms
    void setUniform();
    
private:
    unsigned int m_ID;
};

}
