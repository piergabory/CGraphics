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

Shader::Shader(std::string file, GLenum type) :
    m_identifier(glCreateShader(type))
{
    std::string source = Loaders::loadFile(file);
    GLchar* cstring = (GLchar*)source.c_str();
    glShaderSource(m_identifier, 1, &cstring, nullptr);
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
