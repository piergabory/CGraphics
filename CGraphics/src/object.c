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
    size_t stride = 3 + 3 + 2; /* 9 = pos(3float), normal(3float), UV(2float) */

    vertices = (float*)calloc(stride * num_triangles * 3, sizeof(float));

    // foreacch triangle
    for (face = 0; face < attributes.num_face_num_verts; face++) {
        assert(attributes.face_num_verts[face] % 3 == 0 && "Assume all triangle faces.");
        for (size_t face_vertex_index = 0; face_vertex_index < (size_t)attributes.face_num_verts[face] / 3; face_vertex_index++) {
            for (size_t vertex_index = 0; vertex_index < 3; vertex_index++) {
                tinyobj_vertex_index_t idx = attributes.faces[face_offset + 3 * face_vertex_index + vertex_index];
                size_t byte_position = (3 * face + vertex_index) * stride;

                GLKVector3 vertex = GLKVector3MakeWithArray(attributes.vertices + 3 * (size_t)idx.v_idx);
                GLKVector3 normal = GLKVector3MakeWithArray(attributes.normals + 3 * (size_t)idx.vn_idx);
                GLKVector2 uv = GLKVector2MakeWithArray(attributes.texcoords + 3 * (size_t)idx.vt_idx);

                memcpy(vertices + byte_position + 0, vertex.v, 3 * sizeof(float));
                memcpy(vertices + byte_position + 3, normal.v, 3 * sizeof(float));
                memcpy(vertices + byte_position + 6, uv.v, 2 * sizeof(float));
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
    glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, (GLsizei) stride * sizeof(float), (void*)(0 * sizeof(float)));

    glEnableVertexAttribArray(NORMAL_ATTRIBUTE_POSITION);
    glVertexAttribPointer(NORMAL_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, (GLsizei) stride * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(UV_ATTRIBUTE_POSITION);
    glVertexAttribPointer(UV_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, (GLsizei) stride * sizeof(float), (void*)(6 * sizeof(float)));

    free(vertices);
    tinyobj_attrib_free(&attributes);
    tinyobj_shapes_free(shapes, shape_count);
    tinyobj_materials_free(materials, material_count);

    Material mat = {
        .shine = 32,
        .specular = 0.3,
        .diffuse = 0.7,
        .texture = 0
    };

    new_object.material = mat;
    new_object.shader = program;

    return new_object;
}

void useMaterial(Object object) {
    glUniform1f(object.shader.uniform_material_shine, object.material.shine);
    glUniform1f(object.shader.uniform_material_specular, object.material.specular);
    glUniform1f(object.shader.uniform_material_diffuse, object.material.diffuse);
    glUniform3fv(object.shader.uniform_material_color, 1, object.material.color.v);
    glBindTexture(GL_TEXTURE_2D, object.material.texture);
}


Object importTexturedOBJ(char* filepath, char* texturepath, ShaderProgram program) {
    Object new_object = importOBJ(filepath, program);
    new_object.material.texture = loadTexture(texturepath);
    return new_object;
}

/**
 * Draw Object
 * Renders the object.
 */
void bindObject(Object object) {
    glBindVertexArray(object.vao);
    glUseProgram(object.shader.id);
    useMaterial(object);
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
    glDeleteTextures(1, &object.material.texture);
}
