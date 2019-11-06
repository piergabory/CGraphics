//
//  Scene.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Scene.hpp"

namespace Gabengine {

// constructor
Scene::Scene():
camera(GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90), 1, 0.1f, 100.f))
{}

void Scene::render() {
    std::stack<Mesh*> renderStack;
    std::stack<Object*> buffer;

    // Fill render queue
    // tree scan
    buffer.push(this);
    Object *current;

    while (!buffer.empty()) {
        current = buffer.top();
        buffer.pop();
        for (Object* children: current->childrens()) {
            buffer.push(children);
        }
        
        if (typeid(*current) == typeid(Mesh)) {
            renderStack.push((Mesh*)current);
        }
    }

    while (!renderStack.empty()) {
        renderStack.top()->render(camera);
        renderStack.pop();
    }
}

}
