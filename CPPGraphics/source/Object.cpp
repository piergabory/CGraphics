//
//  Object.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Object.hpp"

namespace Gabengine {

Object::Object() {
    modelViewStates.push(GLKMatrix4Identity);
}

Object::~Object() {
    while (!childrens().empty()) {
        Object* topChildren = childrens().back();
        childrens().pop_back();
        delete topChildren;
    }
}

void Object::add(Object *children) {
    m_childrens.push_back(children);
}

}
