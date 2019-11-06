//
//  Material.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Material.hpp"

namespace Gabengine {

Material::Material(const std::string &vertexShader, const std::string &fragmentShader) :
    m_programID(glCreateProgram())
{
    GLuint vertexShaderID = Shader::getVertex(vertexShader);
    GLuint fragmentShaderID = Shader::getFragment(fragmentShader);
    glAttachShader(m_programID, vertexShaderID);
    glAttachShader(m_programID, fragmentShaderID);
    glLinkProgram(m_programID);
}

BasicMaterial::BasicMaterial():
    Material("shader/perspective.glsl","shader/flat.glsl"),
    modelViewProjectionMatrixUniform(glGetUniformLocation(programID(), "model_view_projection_matrix_uniform")),
    modelViewMatrixUniform(glGetUniformLocation(programID(), "model_view_matrix_uniform")),
    normalMatrixUniform(glGetUniformLocation(programID(), "normal_matrix_uniform"))
{}

}


