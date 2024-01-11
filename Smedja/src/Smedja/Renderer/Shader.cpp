#include "Shader.h"
#include "Smedja/Log.h"
#include <glad/glad.h>

namespace Smedja {

Shader::Shader(const std::string &vertPath, const std::string &fragPath) {
    std::string vShaderCode;
    std::string fShaderCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertPath);
        fShaderFile.open(fragPath);
        std::stringstream vShaderStream, fShaderStream;

        // read buffers into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handles
        vShaderFile.close();
        fShaderFile.close();

        // convert stream to string
        vShaderCode = vShaderStream.str();
        fShaderCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        SD_WARN("Error reading shader files. Vertex Path: {0}  Frag Path: {1}",
                vertPath, fragPath);
    }

    const char *vertSource = vShaderCode.c_str();
    const char *fragSource = fShaderCode.c_str();

    init(vertSource, fragSource);
}

Shader::Shader() {}

Shader::~Shader() {
    glDeleteProgram(m_ID);
}

void Shader::init(const char *vertSource, const char *fragSource) {
    unsigned int vShader, fShader;
    int success;
    char infoLog[512];

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertSource, NULL);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        SD_CORE_ERROR("Vertex shader compilation failed: {}", infoLog);
    }

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fragSource, NULL);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        SD_CORE_ERROR("Fragment shader compilation failed: {}", infoLog);
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vShader);
    glAttachShader(m_ID, fShader);
    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(m_ID, 512, NULL, infoLog);
        SD_CORE_ERROR("{}", infoLog);
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::bind() {
    glUseProgram(m_ID);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::setUniform1f(const std::string &name, float v0) {
    glUniform1f(getUniformLocation(name), v0);
}

void Shader::setUniform2f(const std::string &name, float v0, GLfloat v1) {
    glUniform2f(getUniformLocation(name), v0, v1);
}

void Shader::setUniform3f(const std::string &name, float v0, GLfloat v1,
                          float v2) {
    glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4f(const std::string &name, float v0, GLfloat v1,
                          float v2, GLfloat v3) {
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform1i(const std::string &name, int v0) {
    glUniform1i(getUniformLocation(name), v0);
}

void Shader::setUniform2i(const std::string &name, int v0, int v1) {
    glUniform2i(getUniformLocation(name), v0, v1);
}

void Shader::setUniform3i(const std::string &name, int v0, int v1, int v2) {
    glUniform3i(getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4i(const std::string &name, int v0, int v1, int v2,
                          int v3) {
    glUniform4i(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform1ui(const std::string &name, unsigned int v0) {
    glUniform1ui(getUniformLocation(name), v0);
}

void Shader::setUniform2ui(const std::string &name, unsigned int v0,
                           unsigned int v1) {
    glUniform2ui(getUniformLocation(name), v0, v1);
}

void Shader::setUniform3ui(const std::string &name, unsigned int v0,
                           unsigned int v1, unsigned int v2) {
    glUniform3ui(getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4ui(const std::string &name, unsigned int v0,
                           unsigned int v1, unsigned int v2, unsigned int v3) {
    glUniform4ui(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat2x2(const std::string &name, const float *value) {
    glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat3x3(const std::string &name, const float *value) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat4x4(const std::string &name, const float *value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat2x3(const std::string &name, const float *value) {
    glUniformMatrix2x3fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat3x2(const std::string &name, const float *value) {
    glUniformMatrix3x2fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat2x4(const std::string &name, const float *value) {
    glUniformMatrix2x4fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat4x2(const std::string &name, const float *value) {
    glUniformMatrix4x2fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat3x4(const std::string &name, const float *value) {
    glUniformMatrix3x4fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat4x3(const std::string &name, const float *value) {
    glUniformMatrix4x3fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::setUniformMat2x2(const std::string &name, const glm::mat2x2 &mat) {
    glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat3x3(const std::string &name, const glm::mat3x3 &mat) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat4x4(const std::string &name, const glm::mat4x4 &mat) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat2x3(const std::string &name, const glm::mat2x3 &mat) {
    glUniformMatrix2x3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat3x2(const std::string &name, const glm::mat3x2 &mat) {
    glUniformMatrix3x2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat2x4(const std::string &name, const glm::mat2x4 &mat) {
    glUniformMatrix2x4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat4x2(const std::string &name, const glm::mat4x2 &mat) {
    glUniformMatrix4x2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat3x4(const std::string &name, const glm::mat3x4 &mat) {
    glUniformMatrix3x4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat4x3(const std::string &name, const glm::mat4x3 &mat) {
    glUniformMatrix4x3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::getUniformLocation(const std::string &name) {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_ID, name.c_str());
    SD_CORE_ASSERT(location != -1, "Uniform {0} does not exist!", name);
    m_uniformLocationCache[name] = location;
    return location;
}

}; // namespace Smedja
