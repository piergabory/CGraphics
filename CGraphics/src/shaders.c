//
//  shaders.c
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "shaders.h"


/**
 * Print shader compile log
 *
 * Print out in  the standard output the compiling logs of the provided shader
 * @param shader Compiled shader
 */
static void printShaderCompileLog(Shader shader) {
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    char* log= malloc(length * sizeof(char));
    glGetShaderInfoLog(shader, length, 0, log);
    fprintf(stderr, "%s\n", log);
    free(log);
}


/**
 * Load shader
 *
 * Loads a shader from a file, and compiles it based on a provided type
 * If the source code contains errors, the compilation log will be displayed in the standard output
 * @see printShaderCompileLog
 * @see shaderSourceFile
 *
 * @param shader_file relative path to the shader's source code
 * @param shader_type GL enum value, either:
 *  - GL_VERTEX_SHADER to compile a vertex shader
 *  - GL_FRAGMENT_SHADER to compile a fragment shader
 * @return compiled shader
 */
static Shader loadShader(char* shader_file, GLenum shader_type) {
    GLint status;
    GLuint shader = glCreateShader(shader_type);
    char* source_code = loadFile(shader_file);

    if (source_code == NULL) return 0;

    glShaderSource(shader, 1,(const GLchar**)&source_code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        fprintf(stderr, "Failed to compile shader: %s\n", "vertex_shader.glsl");
        printShaderCompileLog(shader);
    }
    free(source_code);
    return shader;
}


/// TODO: Doc
static void linkProgram(GLuint programId, Shader vertex_shader, Shader fragment_shader) {
    glAttachShader(programId, vertex_shader);
    glAttachShader(programId, fragment_shader);
    glLinkProgram(programId);
}


/// TODO: Doc
static void mapUniforms(ShaderProgram* program) {
    program->uniform_model_view_projection_matrix = glGetUniformLocation(program->id,"model_view_projection_matrix_uniform");
    program->uniform_model_view_matrix =            glGetUniformLocation(program->id,"model_view_matrix_uniform");
    program->uniform_normal_matrix =                glGetUniformLocation(program->id, "normal_matrix_uniform");
    program->uniform_material_shine = glGetUniformLocation(program->id,"material.shine");
    program->uniform_material_specular = glGetUniformLocation(program->id,"material.specular");
    program->uniform_material_diffuse = glGetUniformLocation(program->id,"material.diffuse");
    program->uniform_material_color = glGetUniformLocation(program->id,"material.color");
    program->uniform_lights_position = glGetUniformLocation(program->id, "lights[0].position");
    program->uniform_lights_color = glGetUniformLocation(program->id, "lights[0].color");
    program->uniform_light_count = glGetUniformLocation(program->id, "light_count");
}


/**
 * Shader Program
 *
 * @param vertex_shader_file  Path to the vertex shader source code.
 * @param fragment_shader_file  Path to the fragment shader source code.
 * @return compiled and linked shader program.
 */
ShaderProgram shaderProgram(char* vertex_shader_file, char* fragment_shader_file) {
    ShaderProgram shader_program;
    shader_program.id = glCreateProgram();

    Shader vertex_shader = loadShader(vertex_shader_file, GL_VERTEX_SHADER);
    Shader fragment_shader = loadShader(fragment_shader_file, GL_FRAGMENT_SHADER);
    linkProgram(shader_program.id, vertex_shader, fragment_shader);
    mapUniforms(&shader_program);

    return shader_program;
}

void updateUniforms(ShaderProgram program, GLKMatrix4 model_view, GLKMatrix4 projection) {
    GLKMatrix4 model_view_projection = GLKMatrix4Multiply(projection, model_view);
    GLKMatrix4 normal = GLKMatrix4Invert(model_view, NULL);
    glUseProgram(program.id);
    glUniformMatrix4fv(program.uniform_model_view_projection_matrix, 1, GL_FALSE, model_view_projection.m);
    glUniformMatrix4fv(program.uniform_model_view_matrix, 1, GL_FALSE, model_view.m);
    glUniformMatrix4fv(program.uniform_normal_matrix, 1, GL_TRUE, normal.m);
}

void updateLights(ShaderProgram program, Light* lights[], GLsizei lightCount) {
    glUniform1i(program.uniform_light_count, lightCount);
    for (GLsizei index = 0; index < lightCount; index++) {
        glUniform4fv(program.uniform_lights_color + 2 * index, 1, lights[index]->color.v);
        glUniform3fv(program.uniform_lights_position + 2 * index, 1, lights[index]->position.v);
    }
}
