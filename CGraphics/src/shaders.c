//
//  shaders.c
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "shaders.h"

static GLchar* shaderSourceFile(char* path) {
    FILE* stream = fopen(path, "r");
    if (stream == NULL) {
        printf("File error: Failed to load shader: %s\n", path);
        return NULL;
    }
    fseek(stream, 0L, SEEK_END);
    size_t size = ftell(stream) + 1;
    if (size == 0) {
        printf("File warning: empty shader source file: %s\n", path);
    }
    GLchar* source = (GLchar*)malloc(size * sizeof(GLchar));
    rewind(stream);
    fread(source, size, sizeof(char), stream);
    source[size - 1] = '\0';
    return source;
}

static void printShaderCompileLog(GLuint shaderIdentifier) {
    GLint length;
    glGetShaderiv(shaderIdentifier, GL_INFO_LOG_LENGTH, &length);
    char* log= malloc(length * sizeof(char));
    glGetShaderInfoLog(shaderIdentifier, length, 0, log);
    printf("%s\n", log);
    free(log);
}

static Shader loadShader(char* shader_file, GLenum shader_type) {
    GLint status;
    GLuint shader = glCreateShader(shader_type);
    const GLchar *source_code = shaderSourceFile(shader_file);

    glShaderSource(shader, 1, &source_code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        printf("Failed to compile shader: %s\n", "vertex_shader.glsl");
        printShaderCompileLog(shader);
    }
    free((void *)source_code);
    return shader;
}

ShaderProgram shaderProgram(char* vertex_shader_file, char* fragment_shader_file) {
    ShaderProgram shader_program = glCreateProgram();
    Shader vertex_shader = loadShader(vertex_shader_file, GL_VERTEX_SHADER);
    Shader fragment_shader = loadShader(fragment_shader_file, GL_FRAGMENT_SHADER);

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    return shader_program;
}



