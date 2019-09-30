//
//  scene.h
//  CGraphics
//
//  Created by Pierre Gabory on 29/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef scene_h
#define scene_h

#include "object.h"

#include <GLKit/GLKMath.h>

#define GLKMatrix4Identity GLKMatrix4Make(\
            1, 0, 0, 0,\
            0, 1, 0, 0,\
            0, 0, 1, 0,\
            0, 0, 0, 1\
        );


typedef struct Instance {
    Object* model;
    GLKMatrix4 model_view;

    struct Instance* next;
} Instance;

typedef struct Scene {
    Instance* root;
    GLKMatrix4 camera;
} Scene;

Scene createScene(void);

void deleteScene(Scene newScene);

Instance* createInstance(Object* model);

void deleteInstance(Instance* instance);

Instance* addObjectToScene(Object* model, Scene* scene);

void drawScene(Scene scene);

#endif /* scene_h */
