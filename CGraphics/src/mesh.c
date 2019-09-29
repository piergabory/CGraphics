//
//  mesh.c
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "mesh.h"

static GLuint createVertexBufferFromMesh(Mesh mesh) {
    GLuint vertex_buffer_object;
    size_t buffer_size = mesh.size * (mesh.color_size + mesh.point_size) * sizeof(GLfloat);

    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, mesh.vertices, GL_STATIC_DRAW);

    return vertex_buffer_object;
}

Mesh createMesh(float* vertices, size_t count, unsigned int point_size, unsigned int color_size) {
    Mesh mesh;
    mesh.vertices = vertices;
    mesh.size = count;
    mesh.point_size = point_size;
    mesh.color_size = color_size;

    return mesh;
}

Object createObject(Mesh mesh, ShaderProgram shader_program) {
    Object object;
    glGenVertexArrays(1, &object.vao);
    glBindVertexArray(object.vao);

    glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
    glEnableVertexAttribArray(COLOR_ATTRIBUTE_POSITION);

    object.vbo = createVertexBufferFromMesh(mesh);
    glBindBuffer(GL_ARRAY_BUFFER, object.vbo);

    GLsizei vertexSize = (mesh.point_size + mesh.color_size) * sizeof(GLfloat);
    void* colorByteOffset = (void*)( mesh.point_size * sizeof(GLfloat));
    glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, mesh.point_size, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glVertexAttribPointer(COLOR_ATTRIBUTE_POSITION,  mesh.color_size, GL_FLOAT, GL_FALSE, vertexSize, colorByteOffset);


    object.shader_program = shader_program;

    return object;
}

void drawObject(Object object) {
    glBindVertexArray(object.vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(object.shader_program);
}

void deleteObject(Object object) {
    glDeleteBuffers(1, &object.vbo);
    glDeleteBuffers(1, &object.vao);
}
