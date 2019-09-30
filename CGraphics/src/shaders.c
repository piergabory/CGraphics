//
//  shaders.c
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "shaders.h"


/**
 * Shader source file
 *
 * Returns a string of all the content of a source code file
 *
 * @param path relative file path to the source code
 * @return string content of the source code file
 */
static GLchar* shaderSourceFile(char* path) {
    FILE* stream = fopen(path, "r");
    if (stream == NULL) {
        fprintf(stderr, "File error: Failed to load shader: %s\n", path);
        return NULL;
    }
    fseek(stream, 0L, SEEK_END);
    size_t size = ftell(stream) + 1;
    if (size == 0) {
        fprintf(stderr, "File warning: empty shader source file: %s\n", path);
    }
    GLchar* source = (GLchar*)malloc(size * sizeof(GLchar));
    rewind(stream);
    fread(source, size, sizeof(char), stream);
    source[size - 1] = '\0';
    return source;
}


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
    const GLchar *source_code = shaderSourceFile(shader_file);

    glShaderSource(shader, 1, &source_code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        fprintf(stderr, "Failed to compile shader: %s\n", "vertex_shader.glsl");
        printShaderCompileLog(shader);
    }
    free((void *)source_code);
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
    program->uniform_model_view_matrix = glGetUniformLocation(program->id,"model_view_matrix_uniform");
    program->uniform_normal_matrix = glGetUniformLocation(program->id, "normal_matrix_uniform");
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
