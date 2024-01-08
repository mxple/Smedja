#include "Shader.h"
#include "Smedja/Log.h"
#include <glad/glad.h>

namespace Smedja {

Shader::Shader(std::string &vertPath, std::string &fragPath) {
    std::string   vShaderCode;
    std::string   fShaderCode;
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
    } 
    catch (std::ifstream::failure e) {
        SD_WARN("Error reading shader files. Vertex Path: {0}  Frag Path: {1}",
                vertPath, fragPath);
    }

    const char* vertSource = vShaderCode.c_str();
    const char* fragSource = vShaderCode.c_str();

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

}; // namespace Smedja
