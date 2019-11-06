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
#include <stack>
#include <GLKit/GLKMath.h>

namespace Gabengine {

class Object {
public:
    void add(Object *children);

    Object();

    virtual ~Object();

    inline void translate(float x, float y, float z) { modelViewWriteRef() = GLKMatrix4Translate(modelView(), x, y, z); }

    inline void scale(float x, float y, float z) { modelViewWriteRef() = GLKMatrix4Scale(modelView(), x, y, z); }

    inline void scale(float x) { scale(x,x,x); }

    inline void rotate(float degrees, float x, float y, float z) {
        modelViewWriteRef() = GLKMatrix4Rotate(modelView(), GLKMathDegreesToRadians(degrees), x, y, z);
    }

    inline void save() { modelViewStates.push(modelView()); }

    inline void restore() { modelViewStates.pop(); }

    // public read
    inline const GLKMatrix4& modelView() const { return modelViewStates.top(); }

    inline std::vector<Object*> childrens() const { return m_childrens; }

private:
    // private write
    inline GLKMatrix4& modelViewWriteRef() { return modelViewStates.top(); }

    std::stack<GLKMatrix4> modelViewStates;
    std::vector<Object*> m_childrens = {};
};

}

#endif /* Object_hpp */
