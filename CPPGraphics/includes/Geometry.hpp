//
//  Geometry.hpp
//  Gabengine
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <vector>
#include <cstdlib>

#include <GL/glew.h>
#include <GLKit/GLKMath.h>


namespace Gabengine {

struct Vertex {
    GLKVector3 position;
    GLKVector3 normal;
    GLKVector2 uv;
};


class Geometry {
public:
    inline GLuint vertexArray() { return m_vao; }
    inline GLuint vertexCount() { return m_vertexCount; }


private:
    // Properties
    GLuint m_vbo = 0;
    GLuint m_vao = 0;
    GLsizei m_vertexCount;

    // Constructor / Destructor
    Geometry(std::vector<Vertex> &vertices);
    ~Geometry();

    enum VertexAttributes {
        Position = 0,
        Normal = 1,
        UV = 2
    };
};

}


#endif /* Geometry_hpp */
