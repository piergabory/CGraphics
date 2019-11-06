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

    Vertex( GLKVector3 position, GLKVector3 normal, GLKVector2 uv ):
    position(position), normal(normal), uv(uv)
    {}
};


class Geometry {
public:
    inline GLuint vertexArray() { return m_vao; }
    inline GLuint vertexCount() { return m_vertexCount; }

    inline void bindGeometry() { glBindVertexArray(m_vao); }

    // Constructor / Destructor
    Geometry(const std::vector<Vertex> &vertices);
    Geometry(const GLfloat *data, const GLsizei vertex_count);
    ~Geometry();
private:
    // Properties
    GLuint m_vbo = 0;
    GLuint m_vao = 0;
    GLsizei m_vertexCount;
    
    enum VertexAttributes {
        Position = 0,
        Normal = 1,
        UV = 2
    };
};

}


#endif /* Geometry_hpp */
