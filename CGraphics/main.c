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

    addLightSource(&scene, GLKVector3Make(10, 0, 0));

    ShaderProgram shader_program = shaderProgram(
        "shaders/vertex_shader.glsl",
        "shaders/fragment_shader.glsl"
    );

    Object triangle = importOBJ("assets/teapot.obj", shader_program);

    Instance* triangle_instance = addObjectToScene(&triangle, &scene);
    float scale = 0.3;
    triangle_instance->model_view = GLKMatrix4Translate(triangle_instance->model_view, 0, 0, -2);
    triangle_instance->model_view = GLKMatrix4Scale(triangle_instance->model_view, scale, scale, scale);
    

    // Event loop
    while(!glfwWindowShouldClose(window))
    {
        triangle_instance->model_view = GLKMatrix4Rotate(triangle_instance->model_view,0.0001, 0, 1, 0);
        triangle_instance->model_view = GLKMatrix4Rotate(triangle_instance->model_view,0.00005, 0, 0, 1);
        triangle_instance->model_view = GLKMatrix4Rotate(triangle_instance->model_view,0.0002, 0, 1, 0);

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
