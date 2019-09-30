//
//  window.c
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "window.h"

Window initContext() {

    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
      fprintf(stderr, "ERROR: could not start GLFW3\n");
      exit(1);
    }

    // uncomment these lines if on Apple OS X
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 640, "Hello Triangle", NULL, NULL);
    if (!window) {
      fprintf(stderr, "ERROR: could not open window with GLFW3\n");
      glfwTerminate();
      exit(1);
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

    return window;
}
