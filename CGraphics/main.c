//
//  main.c
//  CGraphics
//
//  Created by Pierre Gabory on 27/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#define CG_CONTEXT_SHOW_BACKTRACE
#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

GLchar* shaderSourceFile(char* path) {
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

void printShaderCompileLog(GLuint shaderIdentifier) {
    GLint length;
    glGetShaderiv(shaderIdentifier, GL_INFO_LOG_LENGTH, &length);
    char* log= malloc(length * sizeof(char));
    glGetShaderInfoLog(shaderIdentifier, length, 0, log);
    printf("%s\n", log);
    free(log);
}

// Define main function
int main()
{
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
      fprintf(stderr, "ERROR: could not start GLFW3\n");
      return 1;
    }

    // uncomment these lines if on Apple OS X
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
      fprintf(stderr, "ERROR: could not open window with GLFW3\n");
      glfwTerminate();
      return 1;
    }
    glfwMakeContextCurrent(window);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"


    // Loading Shader

    GLint status;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertex_shader_source = shaderSourceFile("shaders/vertex_shader.glsl");
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        printf("Failed to compile shader: %s\n", "vertex_shader.glsl");
        printShaderCompileLog(vertex_shader);
    }
    free((void *)vertex_shader_source);


    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragment_shader_source = shaderSourceFile("shaders/fragment_shader.glsl");
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        printf("Failed to compile shader: %s\n", "fragment_shader.glsl");
        printShaderCompileLog(fragment_shader);
    }
    free((void *)fragment_shader_source);


    // Compile shader program

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fragment_shader);
    glAttachShader(shader_programme, vertex_shader);
    glLinkProgram(shader_programme);


    // Load Vertices

    // INIT Vertex Buffer
    GLfloat vertices[] = {
        -0.5f, -0.5f,  0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.0f,     0.0f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f,     0.0f, 0.0f, 1.0f
    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint COLOR_ATTR_POSITION = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(COLOR_ATTR_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)( 0 * sizeof(GLfloat)));
    glVertexAttribPointer(COLOR_ATTR_POSITION,  3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)( 3 * sizeof(GLfloat)));


    // Event loop
    while(!glfwWindowShouldClose(window))
    {
        sleep(1.0/30.0);

        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);

    // Terminate GLFW
    glfwTerminate(); return 0;
}
