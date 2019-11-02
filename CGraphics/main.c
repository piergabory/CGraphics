//
//  main.c
//  CGraphics
//
//  Created by Pierre Gabory on 27/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//
// yo dude
#define CG_CONTEXT_SHOW_BACKTRACE
#define GL_SILENCE_DEPRECATION

#include <unistd.h>


#include "shader_programs.h"
#include "window.h"
#include "scene.h"


// Define main function
int main()
{
    Window window = initContext();
    Scene scene = createScene();

    addLightSource(&scene, GLKVector3Make(-10, 0, 0), GLKVector4Make(1.0f, 0.3f, 0.0f, 0.01));
    addLightSource(&scene, GLKVector3Make(10, 0, -10), GLKVector4Make(0.0f, 0.6f, 1.0f, 0.02));
    addLightSource(&scene, GLKVector3Make(0, 5, 0), GLKVector4Make(1.0, 1.0, 1.0, 1.0));

    Object skybox_object = importTexturedOBJ("assets/skybox.obj", "assets/textures/skybox.png", make_skybox_shader_program());
    Object teapot_object = importTexturedOBJ("assets/teapot.obj", "assets/textures/null.png", make_basic_shader_program());

    Instance* skybox = addObjectToScene(&skybox_object, &scene);
    float skybox_scale = 60;
    skybox->model_view = GLKMatrix4Scale(skybox->model_view, skybox_scale, skybox_scale, skybox_scale);


    Instance* teapot = addObjectToScene(&teapot_object, &scene);
    float teapot_scale = 0.3;
    teapot->model_view = GLKMatrix4Translate(teapot->model_view, 0, 0, -2);
    teapot->model_view = GLKMatrix4Scale(teapot->model_view, teapot_scale, teapot_scale, teapot_scale);

    // Event loop
    while(!glfwWindowShouldClose(window))
    {
        teapot->model_view = GLKMatrix4Rotate(teapot->model_view,0.0001, 1, 1, 0);
        teapot->model_view = GLKMatrix4Rotate(teapot->model_view,0.00005, 0, 0, 1);
        teapot->model_view = GLKMatrix4Rotate(teapot->model_view,0.0002, 0, 1, 0);

        skybox->model_view = GLKMatrix4Rotate(skybox->model_view,0.00002, 0, 1, 0);

        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawScene(scene);
        glfwPollEvents();
        glfwSwapBuffers(window);
        sleep(1.0/30.0);
    }

    
    deleteObject(teapot_object);
    deleteObject(skybox_object);
    deleteScene(scene);

    // Terminate GLFW
    glfwTerminate(); return 0;
}
