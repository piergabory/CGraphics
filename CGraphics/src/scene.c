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
    newScene.lights = NULL;
    return newScene;
}

void deleteScene(Scene newScene) {
    deleteInstance(newScene.root);
    for (size_t index = 0; index < newScene.light_count; index++) {
        free(newScene.lights[index]);
    }
    free(newScene.lights);
}

void addLightSource(Scene* scene, GLKVector3 position, GLKVector4 color) {
    Light* newLight = malloc(sizeof(Light));
    newLight->position = position;
    newLight->color = color;
    scene->light_count += 1;
    scene->lights = realloc(scene->lights, sizeof(Light*) * scene->light_count);
    scene->lights[scene->light_count - 1] = newLight;
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
        bindObject(*head->model);
        updateUniforms(head->model->shader, head->model_view, scene.camera);
        updateLights(head->model->shader, scene.lights, (GLsizei) scene.light_count);
        glDrawArrays(GL_TRIANGLES, 0, head->model->vertices_count);
        head = head->next;
    }
}
