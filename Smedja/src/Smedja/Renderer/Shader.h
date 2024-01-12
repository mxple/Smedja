#pragma once

#include "pch.h"

#include <glm/glm.hpp>

namespace Smedja {

class Shader {
public:
    Shader(); // no arg constructor for when we pass in code directly
    Shader(const std::string &vertPath, const std::string &fragPath);
    ~Shader();

    // takes in source code for shaders and then compiles + links them
    void init(const char *vertSource, const char *fragSource);

    void bind();
    void unbind();

    // uniforms
    // see https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
    void setUniform1f(const std::string &name, float v0);

    void setUniform2f(const std::string &name, float v0, float v1);

    void setUniform3f(const std::string &name, float v0, float v1, float v2);

    void setUniform4f(const std::string &name, float v0, float v1, float v2,
                      float v3);

    void setUniform2f(const std::string &name, const glm::vec2 &vec);

    void setUniform3f(const std::string &name, const glm::vec3 &vec);

    void setUniform4f(const std::string &name, const glm::vec4 &vec);

    void setUniform1i(const std::string &name, int v0);

    void setUniform2i(const std::string &name, int v0, int v1);

    void setUniform3i(const std::string &name, int v0, int v1, int v2);

    void setUniform4i(const std::string &name, int v0, int v1, int v2, int v3);

    void setUniform1ui(const std::string &name, unsigned int v0);

    void setUniform2ui(const std::string &name, unsigned int v0,
                       unsigned int v1);

    void setUniform3ui(const std::string &name, unsigned int v0,
                       unsigned int v1, unsigned int v2);

    void setUniform4ui(const std::string &name, unsigned int v0,
                       unsigned int v1, unsigned int v2, unsigned int v3);

    void setUniformMat2x2(const std::string &name, const float *value);

    void setUniformMat3x3(const std::string &name, const float *value);

    void setUniformMat4x4(const std::string &name, const float *value);

    void setUniformMat2x3(const std::string &name, const float *value);

    void setUniformMat3x2(const std::string &name, const float *value);

    void setUniformMat2x4(const std::string &name, const float *value);

    void setUniformMat4x2(const std::string &name, const float *value);

    void setUniformMat3x4(const std::string &name, const float *value);

    void setUniformMat4x3(const std::string &name, const float *value);

    void setUniformMat2x2(const std::string &name, const glm::mat2x2 &mat);

    void setUniformMat3x3(const std::string &name, const glm::mat3x3 &mat);

    void setUniformMat4x4(const std::string &name, const glm::mat4x4 &mat);

    void setUniformMat2x3(const std::string &name, const glm::mat2x3 &mat);

    void setUniformMat3x2(const std::string &name, const glm::mat3x2 &mat);

    void setUniformMat2x4(const std::string &name, const glm::mat2x4 &mat);

    void setUniformMat4x2(const std::string &name, const glm::mat4x2 &mat);

    void setUniformMat3x4(const std::string &name, const glm::mat3x4 &mat);

    void setUniformMat4x3(const std::string &name, const glm::mat4x3 &mat);
    // TODO add glm type support

    // public in case user wants to use unsupported uniform setter and
    // still wishes to keep cache functionality
    int getUniformLocation(const std::string &name);

private:
    unsigned int m_ID;
    std::unordered_map<std::string, int> m_uniformLocationCache;
};

} // namespace Smedja
