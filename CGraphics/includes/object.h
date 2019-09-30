//
//  object.h
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

#include <string.h>
#include <GL/glew.h>
#include <GLKit/GLKMath.h>

#include "shaders.h"
#include "loader.h"

/**
 * 3D Object Instance
 *
 * Contains pointer to the shaders, arrays and buffers representing a 3D object
 */
typedef struct Object {
    GLuint vbo;
    GLuint vao;
    GLsizei vertices_count;
    ShaderProgram material;
} Object;

/**
 * Mesh
 *
 * Array of floats representing a 3D shape
 */
typedef struct Mesh {
    GLsizei size;
    unsigned int point_size;
    unsigned int color_size;
    GLfloat* vertices;
} Mesh;


/**
 * Create Mesh
 * @param vertices floating point values data array
 * @param count number of vertices
 * @param point_size number of floats per vertex defining the position
 * @param color_size number of floats per vertex defining the color
 */
Mesh createMesh(GLfloat* vertices, GLsizei count, GLsizei point_size, GLsizei color_size);

/**
 * Create Object
 *
 * @param shape of the object
 * @param material of the object
 */
Object createObject(Mesh shape, ShaderProgram material);

Object importOBJ(char* filepath, ShaderProgram program) ;

/**
 * Draw Object
 * Renders the object.
 */
void bindObject(Object object);

/**
 * Delete Object
 * Removes the buffers from graphics memory.
 * Does not delete shaders
 *
 * @param object object to delete
 */
void deleteObject(Object object);

#endif /* mesh_h */
