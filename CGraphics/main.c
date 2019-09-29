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

#include "shaders.h"
#include "window.h"


// Define main function
int main()
{
    Window window = initContext();

    // Loading Shader
    ShaderProgram shader_program = shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

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
        glUseProgram(shader_program);
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
