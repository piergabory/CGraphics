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
    GLuint uniform_material_struct;
    GLuint uniform_lightpoint_array;
} ShaderProgram;


typedef struct Material {
    float shine;
    float specular;
    float diffuse;
    GLKVector3 color;
} Material;


typedef struct Object {
    GLuint vbo;
    GLuint vao;
    GLsizei vertices_count;
    ShaderProgram shader;
    Material material;
} Object;


typedef struct Instance {
    Object* model;
    GLKMatrix4 model_view;

    struct Instance* next;
} Instance;


typedef struct LightPoint {
    GLKVector3 position;
    GLKVector3 color;
} LightPoint;


typedef struct Scene {
    Instance* root;
    GLKMatrix4 camera;

    LightPoint **lights;
    size_t light_count;
} Scene;

#endif /* structs_h */
