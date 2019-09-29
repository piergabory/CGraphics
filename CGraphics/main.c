//
//  main.c
//  CGraphics
//
//  Created by Pierre Gabory on 27/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#define CG_CONTEXT_SHOW_BACKTRACE
#define GL_SILENCE_DEPRECATION

#include <unistd.h>

#include "shaders.h"
#include "window.h"
#include "object.h"

// Define main function
int main()
{
    Window window = initContext();

    GLfloat vertices[] = {
        -0.5f, -0.5f,  0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.0f,     0.0f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f,     0.0f, 0.0f, 1.0f
    };
    Mesh triangle_mesh = createMesh(vertices, 3, 3, 3);

    ShaderProgram shader_program = shaderProgram(
        "shaders/vertex_shader.glsl",
        "shaders/fragment_shader.glsl"
    );

    Object triangle = createObject(triangle_mesh, shader_program);

    // Event loop
    while(!glfwWindowShouldClose(window))
    {
        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawObject(triangle);
        sleep(1.0/30.0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    
    deleteObject(triangle);

    // Terminate GLFW
    glfwTerminate(); return 0;
}
