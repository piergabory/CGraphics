//
//  shader_programs.h
//  CGraphics
//
//  Created by Pierre Gabory on 16/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef shader_programs_h
#define shader_programs_h

#include "shaders.h"


ShaderProgram make_basic_shader_program() {
    return shaderProgram(
         "shaders/basic.vs.glsl",
         "shaders/basic.fs.glsl"
    );
}

ShaderProgram make_normal_shader_program() {
    return shaderProgram(
         "shaders/normal.vs.glsl",
         "shaders/normal.fs.glsl"
    );
}

ShaderProgram make_skybox_shader_program() {
    return shaderProgram(
         "shaders/skybox.vs.glsl",
         "shaders/skybox.fs.glsl"
    );
}

#endif /* shader_programs_h */
