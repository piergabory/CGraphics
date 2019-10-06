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
#include "structs.h"


Scene createScene(void);

void deleteScene(Scene newScene);

void addLightSource(Scene* scene, GLKVector3 position);

Instance* createInstance(Object* model);

void deleteInstance(Instance* instance);

Instance* addObjectToScene(Object* model, Scene* scene);

void drawScene(Scene scene);

#endif /* scene_h */
