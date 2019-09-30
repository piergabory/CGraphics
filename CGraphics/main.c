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

#include "window.h"
#include "scene.h"


// Define main function
int main()
{
    Window window = initContext();
    Scene scene = createScene();

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

    Instance* triangle_instance = addObjectToScene(&triangle, &scene);
    triangle_instance->model_view = GLKMatrix4Translate(triangle_instance->model_view, 0, 0, -2);
    

    // Event loop
    while(!glfwWindowShouldClose(window))
    {
        triangle_instance->model_view = GLKMatrix4Rotate(triangle_instance->model_view,0.002, 0, 1, 0);
        triangle_instance->model_view = GLKMatrix4Rotate(triangle_instance->model_view,0.001, 0, 0, 1);
        triangle_instance->model_view = GLKMatrix4Rotate(triangle_instance->model_view,0.0002, 1, 0, 0);

        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawScene(scene);
        glfwPollEvents();
        glfwSwapBuffers(window);
        sleep(1.0/30.0);
    }

    
    deleteObject(triangle);
    deleteScene(scene);

    // Terminate GLFW
    glfwTerminate(); return 0;
}
