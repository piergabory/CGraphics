//
//  object.c
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "object.h"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj.h"

Object importOBJ(char* filepath, ShaderProgram program) {
    // Get obj source code
    char* obj_source = loadFile(filepath);
    size_t obj_source_length = strlen(obj_source);

    // Declare tinyobj structures
    tinyobj_attrib_t attributes;
    tinyobj_shape_t* shapes = NULL;
    size_t shape_count;
    tinyobj_material_t *materials = NULL;
    size_t material_count;
    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;

    // Parse source code
    tinyobj_parse_obj(&attributes, &shapes, &shape_count, &materials, &material_count, obj_source, obj_source_length, flags);

    Object new_object;
    float* vertices;
    size_t face_offset = 0;
    size_t face;

    /* Assume triangulated face. */
    size_t num_triangles = attributes.num_face_num_verts;
    size_t stride = 9; /* 9 = pos(3float), normal(3float), color(3float) */

    vertices = (float*)malloc(sizeof(float) * stride * num_triangles * 3);

    // foreacch triangle
    for (face = 0; face < attributes.num_face_num_verts; face++) {
        size_t face_vertex;
        assert(attributes.face_num_verts[face] % 3 == 0); /* assume all triangle faces. */

        for (face_vertex = 0; face_vertex < (size_t)attributes.face_num_verts[face] / 3; face_vertex++) {
            size_t vertex;

            tinyobj_vertex_index_t idx0 = attributes.faces[face_offset + 3 * face_vertex + 0];
            tinyobj_vertex_index_t idx1 = attributes.faces[face_offset + 3 * face_vertex + 1];
            tinyobj_vertex_index_t idx2 = attributes.faces[face_offset + 3 * face_vertex + 2];

            GLKVector3 face_vertex[3] = {
                GLKVector3MakeWithArray(attributes.vertices + 3 * (size_t)idx0.v_idx),
                GLKVector3MakeWithArray(attributes.vertices + 3 * (size_t)idx1.v_idx),
                GLKVector3MakeWithArray(attributes.vertices + 3 * (size_t)idx2.v_idx)
            };

            GLKVector3 face_normal[3] =  {
                GLKVector3MakeWithArray(attributes.normals + 3 * (size_t)idx0.vn_idx),
                GLKVector3MakeWithArray(attributes.normals + 3 * (size_t)idx1.vn_idx),
                GLKVector3MakeWithArray(attributes.normals + 3 * (size_t)idx2.vn_idx)
            };

            for (vertex = 0; vertex < 3; vertex++) {
                // position
                memcpy(vertices + ((3 * face + vertex) * stride + 0), face_vertex[vertex].v, 3 * sizeof(float));
                // normal
                memcpy(vertices + ((3 * face + vertex) * stride + 3), face_normal[vertex].v, 3 * sizeof(float));
                // color
                memcpy(vertices + ((3 * face + vertex) * stride + 6), GLKVector3Make(1.0, 0.5, 0.5).v, 3 * sizeof(float));
            }
        }
        face_offset += (size_t)attributes.face_num_verts[face];
    }

    new_object.vbo = 0;
    new_object.vertices_count = 0;
    if (num_triangles > 0) {
        glGenBuffers(1, &new_object.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, new_object.vbo);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(num_triangles * 3 * stride * sizeof(float)), vertices, GL_STATIC_DRAW);
        new_object.vertices_count = (int)num_triangles * 3;
    }

    glGenVertexArrays(1, &new_object.vao);
    glBindVertexArray(new_object.vao);

    glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
    glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(0 * sizeof(float)));

    glEnableVertexAttribArray(NORMAL_ATTRIBUTE_POSITION);
    glVertexAttribPointer(NORMAL_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(COLOR_ATTRIBUTE_POSITION);
    glVertexAttribPointer(COLOR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));

    free(vertices);

    tinyobj_attrib_free(&attributes);
    tinyobj_shapes_free(shapes, shape_count);
    tinyobj_materials_free(materials, material_count);

    new_object.material = program;

    return new_object;
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
