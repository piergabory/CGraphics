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

    modelViewProjectionMatrixUniform = glGetUniformLocation(m_programID, "model_view_projection_matrix_uniform");
    modelViewMatrixUniform = glGetUniformLocation(m_programID, "model_view_matrix_uniform");
    normalMatrixUniform = glGetUniformLocation(m_programID, "normal_matrix_uniform");
}

void Material::setProjectionMatrices(const GLKMatrix4 &modelViewProjection, const GLKMatrix4 &modelView, const GLKMatrix4 &normal) {
    glUseProgram(programID());
    glUniformMatrix4fv(modelViewProjectionMatrixUniform, 1, GL_FALSE, modelViewProjection.m);
    glUniformMatrix4fv(modelViewMatrixUniform, 1, GL_FALSE, modelView.m);
    glUniformMatrix4fv(normalMatrixUniform, 1, GL_TRUE, normal.m);
}

BasicMaterial::BasicMaterial() :
Material("shader/perspective.vs.glsl", "shader/flat.fs.glsl")
{}

}


