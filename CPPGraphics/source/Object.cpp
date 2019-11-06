//
//  Object.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Object.hpp"

namespace Gabengine {

Object::Object(Object &copy) : m_modelViewMatrix(copy.m_modelViewMatrix)
{}

void Object::add(Object &children) {
    std::unique_ptr<Object> unique_reference = std::make_unique<Object>(children);
    childrens.push_back(std::move(unique_reference));
}

}
