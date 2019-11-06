//
//  Scene.hpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stack>
//#include <vector>
#include <typeinfo>

#include <GL/glew.h>
#include <GLKit/GLKMath.h>

#include "Object.hpp"
#include "Mesh.hpp"

namespace Gabengine {

class Scene : public Object {
public:
    Scene();

    void render();

private:
    GLKMatrix4 camera;
};

}

#endif /* Scene_hpp */
