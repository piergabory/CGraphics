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
int main() {
    Window window = initContext();
    Scene scene = createScene();

    addLightSource(&scene, GLKVector3Make(-10, 0, 0), GLKVector4Make(1.0f, 0.3f, 0.0f, 0.01));
    addLightSource(&scene, GLKVector3Make(10, 0, -10), GLKVector4Make(0.0f, 0.6f, 1.0f, 0.02));
    addLightSource(&scene, GLKVector3Make(0, 5, 0), GLKVector4Make(1.0, 1.0, 1.0, 1.0));

    Geometry skybox_object = importTexturedOBJ("assets/skybox.obj", "assets/textures/skybox.png", make_skybox_shader_program());
    Geometry teapot_object = importTexturedOBJ("assets/teapot.obj", "assets/textures/blank.png", make_basic_shader_program());

    Mesh* skybox = addObjectToScene(&skybox_object, &scene);
    float skybox_scale = 60;
    skybox->model_view = GLKMatrix4Scale(skybox->model_view, skybox_scale, skybox_scale, skybox_scale);


    Mesh* teapot = addObjectToScene(&teapot_object, &scene);
    float teapot_scale = 0.3;
    teapot->model_view = GLKMatrix4Scale(teapot->model_view, teapot_scale, teapot_scale, teapot_scale);

    // Event loop
    double xpos = 0, ypos = 0;
    int button = FALSE;
    while(!glfwWindowShouldClose(window))
        {

        teapot->model_view = GLKMatrix4Rotate(teapot->model_view, 0.001, 0, 1, 0);

        GLKMatrix4 save = scene.camera;

        // Orbit
        scene.camera = GLKMatrix4Translate(scene.camera, 0, 0, -3);
        scene.camera = GLKMatrix4Rotate(scene.camera, ypos * 0.01, 1, 0, 0);
        scene.camera = GLKMatrix4Rotate(scene.camera, xpos * 0.01, 0, -1, 0);

        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawScene(scene);

        scene.camera = save;


        glfwPollEvents();
        glfwSwapBuffers(window);
        glfwGetCursorPos(window, &xpos, &ypos);
        button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        }

    
    deleteObject(teapot_object);
    deleteObject(skybox_object);
    deleteScene(scene);

    // Terminate GLFW
    glfwTerminate(); return 0;
}
