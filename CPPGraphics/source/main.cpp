//
//  main.cpp
//  Gabengine
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Scene.hpp"
#include "Window.hpp"

#include "Mesh.hpp"
#include "Material.hpp"
#include "OBJLoader.hpp"


using namespace Gabengine;

int main(int argc, const char * argv[]) {
    Window window("cpp test");
    Scene scene;

    Mesh* teapot = new Mesh(Loaders::importOBJ("assets/teapot.obj"), new BasicMaterial());
    scene.add(teapot);
    teapot->translate(0, 0, -3);
    teapot->scale(0.6);

    while (true) {
        window.clearBuffer();
        scene.render();
        window.pollEvent();
        window.swapBuffer();
    }

    return 0;
}
