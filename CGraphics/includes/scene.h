//
//  scene.h
//  CGraphics
//
//  Created by Pierre Gabory on 29/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef scene_h
#define scene_h

#include <stdio.h>

#include "object.h"

typedef struct Instance {
    Object* model;
    struct Instance* next;
} Instance;

typedef struct Scene {
    Instance* root;
} Scene;

Scene createScene(void);

void deleteScene(Scene newScene);

Instance* createInstance(Object* model);

void deleteInstance(Instance* instance);

void addObjectToScene(Object* model, Scene* scene);

void drawScene(Scene scene);

#endif /* scene_h */
