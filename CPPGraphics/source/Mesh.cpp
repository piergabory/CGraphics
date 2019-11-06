//
//  Mesh.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Mesh.hpp"

namespace Gabengine {

Mesh::Mesh(Geometry *geometry, Material *material):
geometry(geometry),
material(material)
{}

Mesh::~Mesh() {
    delete geometry;
    delete material;
}

void Mesh::render(GLKMatrix4 &camera) {

    // update shader
    GLKMatrix4 modelViewProjection = GLKMatrix4Multiply(camera, modelView());
    GLKMatrix4 normal = GLKMatrix4Invert(camera, NULL);
    material->setProjectionMatrices(modelViewProjection, modelView(), normal);
    glUseProgram(material->programID());

    // load geometry
    geometry->bindGeometry();

    // ready to draw
    glDrawArrays(GL_TRIANGLES, 0, geometry->vertexCount());
}

}
