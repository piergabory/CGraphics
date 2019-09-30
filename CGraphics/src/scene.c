//
//  scene.c
//  CGraphics
//
//  Created by Pierre Gabory on 29/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "scene.h"

Scene createScene() {
    Scene newScene;
    newScene.root = NULL;
    newScene.camera = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0f), 1.0f, 1.0f, 100.0f);
    return newScene;
}

void deleteScene(Scene newScene) {
    deleteInstance(newScene.root);
}


Instance* createInstance(Object* model) {
    Instance* newInstance = malloc(sizeof(Instance));
    if (!newInstance) {
        fprintf(stderr, "Malloc error.");
        return NULL;
    }

    newInstance->model = model;
    newInstance->model_view = GLKMatrix4Identity;
    newInstance->next = NULL;

    return newInstance;
}

void deleteInstance(Instance* instance) {
    if (instance->next)
        deleteInstance(instance->next);
    free(instance);
}

Instance* addObjectToScene(Object* model, Scene* scene) {
    // try to allocate instance
    Instance* newInstance = createInstance(model);
    if (!newInstance) return NULL;

    // push to the instance list on success
    Instance* head = scene->root;
    scene->root = newInstance;
    scene->root->next = head;
    
    return newInstance;
}

void drawScene(Scene scene) {
    Instance* head = scene.root;
    while (head != NULL) {
        updateUniforms(head->model->material, head->model_view, scene.camera);
        bindObject(*head->model);
        glDrawArrays(GL_TRIANGLES, 0, head->model->vertices_count);
        head = head->next;
    }
}
