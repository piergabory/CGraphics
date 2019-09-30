//
//  shaders.h
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef shaders_h
#define shaders_h

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

#define SHADER_DIR "shaders/"

typedef GLuint Shader;

typedef struct ShaderProgram {
    GLuint id;
    GLuint uniform_model_view_projection_matrix;
    GLuint uniform_model_view_matrix;
    GLuint uniform_normal_matrix;
} ShaderProgram;

/**
 * Shader Attributes
 */
enum ShaderAttributes {
    VERTEX_ATTRIBUTE_POSITION,
    COLOR_ATTRIBUTE_POSITION
};

/**
 * Shader Program
 *
 * @param vertex_shader_file  Path to the vertex shader source code.
 * @param fragment_shader_file  Path to the fragment shader source code.
 * @return compiled and linked shader program.
 */
ShaderProgram shaderProgram(char* vertex_shader_file, char* fragment_shader_file);

// TODO: Error handling

#endif /* shaders_h */
