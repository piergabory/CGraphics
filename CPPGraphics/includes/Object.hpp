//
//  Object.hpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <vector>
#include <memory>
#include <GLKit/GLKMath.h>

namespace Gabengine {

class Object {
public:
    void add(Object &children);

    Object() = default;

    // copy constructor
    Object(Object &copy);

private:
    std::vector<std::unique_ptr<Object>> childrens = {};

    GLKMatrix4 m_modelViewMatrix = GLKMatrix4Identity;
};

}

#endif /* Object_hpp */
