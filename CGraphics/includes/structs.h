//
//  structs.h
//  CGraphics
//
//  Created by Pierre Gabory on 05/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef structs_h
#define structs_h

#include <GLKit/GLKMath.h>

typedef struct ShaderProgram {
    GLuint id;
    GLuint uniform_model_view_projection_matrix;
    GLuint uniform_model_view_matrix;
    GLuint uniform_normal_matrix;
    GLuint uniform_material_shine;
    GLuint uniform_material_specular;
    GLuint uniform_material_diffuse;
    GLuint uniform_material_color;
    GLuint uniform_material_texture;
    GLuint uniform_lights_position;
    GLuint uniform_lights_color;
    GLuint uniform_light_count;
} ShaderProgram;

typedef struct Image {
    size_t width;
    size_t height;
    int alpha;
    unsigned char *bytes;
} Image;


typedef struct Material {
    float shine;
    float specular;
    float diffuse;
    GLKVector3 color;
    GLuint texture;
} Material;


typedef struct Geometry {
    GLuint vbo;
    GLuint vao;
    GLsizei vertices_count;
    ShaderProgram shader;
    Material material;
} Geometry;


typedef struct Mesh {
    Geometry* model;
    struct Mesh* next;
    GLKMatrix4 model_view;
} Mesh;


typedef struct Light {
    GLKVector3 position;
    GLKVector4 color;
} Light;


typedef struct Scene {
    Mesh* root;
    GLKMatrix4 camera;
    Light **lights;
    GLuint environment_map;
    GLKVector4 ambient;
    size_t light_count;
} Scene;

#endif /* structs_h */
