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


// Gen VBA from mesh
// Requires binded VBO
static GLuint createVertexArrayFromMesh(Mesh mesh) {
    GLuint vertex_array_object;
    GLsizei vertex_size = (mesh.point_size + mesh.color_size) * sizeof(GLfloat);
    void* color_bytes_offset = (void*)( mesh.point_size * sizeof(GLfloat));

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // Vertices Positions
    glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
    glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, mesh.point_size, GL_FLOAT, GL_FALSE, vertex_size, 0);

    // Vertices Colors
    glEnableVertexAttribArray(COLOR_ATTRIBUTE_POSITION);
    glVertexAttribPointer(COLOR_ATTRIBUTE_POSITION,  mesh.color_size, GL_FLOAT, GL_FALSE, vertex_size, color_bytes_offset);

    return vertex_array_object;
}


/**
 * Create Mesh
 * @param vertices floating point values data array
 * @param count number of vertices
 * @param point_size number of floats per vertex defining the position
 * @param color_size number of floats per vertex defining the color
 */
Mesh createMesh(GLfloat* vertices, GLsizei count, GLsizei point_size, GLsizei color_size) {
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

    // VBO and VAO
    object.vbo = createVertexBufferFromMesh(shape);
    glBindVertexArray(object.vbo);
    object.vao = createVertexArrayFromMesh(shape);

    //
    object.material = material;
    object.vertices_count = shape.size;

    return object;
}


/**
 * Draw Object
 * Renders the object.
 */
void bindObject(Object object) {
    glBindVertexArray(object.vao);
    glUseProgram(object.material.id);
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
