//
//  mesh.h
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

#include <GL/glew.h>

#include "shaders.h"

enum AttributePositions {
    VERTEX_ATTRIBUTE_POSITION,
    COLOR_ATTRIBUTE_POSITION
};

typedef struct Object {
    GLuint vbo;
    GLuint vao;
    ShaderProgram shader_program;
} Object;

typedef struct Mesh {
    size_t size;
    unsigned int point_size;
    unsigned int color_size;
    GLfloat* vertices;
} Mesh;



Mesh createMesh(float* vertices, size_t count, unsigned int point_size, unsigned int color_size);

Object createObject(Mesh mesh, ShaderProgram shader_program);
void drawObject(Object object);
void deleteObject(Object object);

#endif /* mesh_h */
