//
//  shaders.h
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef shaders_h
#define shaders_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define SHADER_DIR "shaders/"

typedef GLuint Shader;
typedef GLuint ShaderProgram;

ShaderProgram shaderProgram(char* vertex_shader_file, char* fragment_shader_file);

// TODO: Error handling

#endif /* shaders_h */
