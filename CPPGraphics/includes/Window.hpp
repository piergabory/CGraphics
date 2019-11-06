//
//  window.hpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 05/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef window_hpp
#define window_hpp

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Gabengine {

class Window {
public:
    Window(std::string title);

    inline void clearBuffer() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    inline void pollEvent() { glfwPollEvents(); }
    inline void swapBuffer() { glfwSwapBuffers(window); }

private:
    GLFWwindow* window;
};

}
#endif /* window_hpp */
