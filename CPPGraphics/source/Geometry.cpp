//
//  Geometry.cpp
//  Gabengine
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Geometry.hpp"

namespace Gabengine {

Geometry::Geometry(std::vector<Vertex> &vertices) : m_vertexCount((GLsizei)vertices.size())
{
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);

    // set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // set vertex arrays
    void *offset = 0;
    glEnableVertexAttribArray(VertexAttributes::Position);
    glVertexAttribPointer(VertexAttributes::Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);

    offset = (void*)(1 * sizeof(GLKVector3));
    glEnableVertexAttribArray(VertexAttributes::Normal);
    glVertexAttribPointer(VertexAttributes::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);

    offset = (void*)(2 * sizeof(GLKVector3));
    glEnableVertexAttribArray(VertexAttributes::UV);
    glVertexAttribPointer(VertexAttributes::UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);
}


Geometry::~Geometry() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_vao);
}

}
