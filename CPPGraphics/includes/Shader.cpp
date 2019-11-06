//
//  Shader.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Shader.hpp"

namespace Gabengine {

std::map<std::string, Shader> Shader::vertexShaders = {};
std::map<std::string, Shader> Shader::fragmentShaders = {};

const GLuint Shader::getVertex(const std::string shader) {
    if (vertexShaders.find(shader) == vertexShaders.end()) {
        vertexShaders.try_emplace(shader, shader, GL_VERTEX_SHADER);
    }
    return vertexShaders.at(shader).m_identifier;
}

const GLuint Shader::getFragment(std::string shader) {
    if (fragmentShaders.find(shader) == fragmentShaders.end()) {
        fragmentShaders.try_emplace(shader, shader, GL_FRAGMENT_SHADER);
    }
    return fragmentShaders.at(shader).m_identifier;
}


std::string Shader::loadFile(std::string path) {
    FILE* stream = std::fopen(path.c_str(), "r");
    if (stream == nullptr) {
        std::cerr << "File error: Failed to load file:" << path << "\n";
        return "";
    }
    fseek(stream, 0L, SEEK_END);
    size_t size = ftell(stream) + 1;
    if (size == 0) {
        std::cerr << "File warning: empty source file::" << path << "\n";
        return "";
    }
    char* source = new char[size];
    rewind(stream);
    fread(source, size, sizeof(char), stream);
    source[size - 1] = '\0';

    std::string string(source);
    delete[] source;

    return string;
}

Shader::Shader(std::string file, GLenum type) :
    m_identifier(glCreateShader(type))
{
    std::string source = loadFile(file);
    glShaderSource(m_identifier, 1, (const GLchar**)source.c_str(), nullptr);
    glCompileShader(m_identifier);

    GLint status;
    glGetShaderiv(m_identifier, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::cerr << "Failed to compile shader: " << file << "\n";

        // print compile error
        GLint length;
        glGetShaderiv(m_identifier, GL_INFO_LOG_LENGTH, &length);
        char* log = new char[length];
        glGetShaderInfoLog(m_identifier, m_identifier, 0, log);
        std::cerr << log << "\n";
        delete[] log;
    }
}

Shader::~Shader() {
    glDeleteShader(m_identifier);
}

}
