//
//  OBJLoader.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 05/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "OBJLoader.hpp"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj.h"

namespace Gabengine {

namespace Loaders {

Geometry* importOBJ(std::string filepath) {
    // Get obj source code
    const std::string obj_source = Loaders::loadFile(filepath);


    std::vector<Vertex> vertices;

    // Declare tinyobj structures
    tinyobj_attrib_t attributes;
    tinyobj_shape_t* shapes = NULL;
    size_t shape_count;
    tinyobj_material_t *materials = NULL;
    size_t material_count;
    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;

    // Parse source code
    tinyobj_parse_obj(&attributes, &shapes, &shape_count, &materials, &material_count, obj_source.c_str(), obj_source.length(), flags);

    /* Assume triangulated face. */
    size_t face_offset = 0;
    size_t num_triangles = attributes.num_face_num_verts;
    size_t stride = 3 + 3 + 2; /* 9 = pos(3float), normal(3float), UV(2float) */

    // allocate attribute data buffer.
    float* vertice_attributes_buffer = (float*)calloc(stride * num_triangles * 3, sizeof(float));

    // FOR EACH FACE
    for (size_t face_num_verts = 0; face_num_verts < attributes.num_face_num_verts; face_num_verts++) {

        // FOR EACH FACE VERTEX
        size_t face_vertex_count = attributes.face_num_verts[face_num_verts];
        for (size_t face_vertex = 0; face_vertex < face_vertex_count; face_vertex++) {
            tinyobj_vertex_index_t idx = attributes.faces[face_offset + face_vertex];
            float *attribute_byte_position = vertice_attributes_buffer + (3 * face_num_verts + face_vertex) * stride;

            float *vertex = 3 * idx.v_idx + attributes.vertices;
            memcpy(attribute_byte_position + 0, vertex, 3 * sizeof(float));

            float *normal = 3 * idx.vn_idx + attributes.normals;
            memcpy(attribute_byte_position + 3, normal, 3 * sizeof(float));

            float *uv = 2 * idx.vt_idx + attributes.texcoords;
            memcpy(attribute_byte_position + 6, uv, 2 * sizeof(float));
        }

        face_offset += (size_t)attributes.face_num_verts[face_num_verts];
    }
//
//    free(vertice_attributes_buffer);
//    tinyobj_attrib_free(&attributes);
//    tinyobj_shapes_free(shapes, shape_count);
//    tinyobj_materials_free(materials, material_count);

    return new Geometry(vertices);
}

}

}
