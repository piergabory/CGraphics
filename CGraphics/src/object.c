//
//  object.c
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "object.h"

// Gen VBO from a mesh struct
static GLuint createVertexBufferFromMesh(Mesh mesh) {
    GLuint vertex_buffer_object;
    size_t buffer_size = mesh.size * (mesh.color_size + mesh.point_size) * sizeof(GLfloat);

    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, mesh.vertices, GL_STATIC_DRAW);

    return vertex_buffer_object;
}


/**
 * Create Mesh
 * @param vertices floating point values data array
 * @param count number of vertices
 * @param point_size number of floats per vertex defining the position
 * @param color_size number of floats per vertex defining the color
 */
Mesh createMesh(float* vertices, size_t count, unsigned int point_size, unsigned int color_size) {
    Mesh mesh;
    mesh.vertices = vertices;
    mesh.size = count;
    mesh.point_size = point_size;
    mesh.color_size = color_size;

    return mesh;
}


/**
 * Create Object
 *
 * @param shape of the object
 * @param material of the object
 */
Object createObject(Mesh shape, ShaderProgram material) {
    Object object;
    glGenVertexArrays(1, &object.vao);
    glBindVertexArray(object.vao);

    glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
    glEnableVertexAttribArray(COLOR_ATTRIBUTE_POSITION);

    object.vbo = createVertexBufferFromMesh(shape);
    glBindBuffer(GL_ARRAY_BUFFER, object.vbo);

    GLsizei vertexSize = (shape.point_size + shape.color_size) * sizeof(GLfloat);
    void* colorByteOffset = (void*)( shape.point_size * sizeof(GLfloat));
    glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, shape.point_size, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glVertexAttribPointer(COLOR_ATTRIBUTE_POSITION,  shape.color_size, GL_FLOAT, GL_FALSE, vertexSize, colorByteOffset);


    object.material = material;

    return object;
}


/**
 * Draw Object
 * Renders the object.
 */
void drawObject(Object object) {
    glBindVertexArray(object.vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(object.material);
}


/**
 * Delete Object
 * Removes the buffers from graphics memory.
 * Does not delete shaders
 *
 * @param object object to delete
 */
void deleteObject(Object object) {
    glDeleteBuffers(1, &object.vbo);
    glDeleteBuffers(1, &object.vao);
}
