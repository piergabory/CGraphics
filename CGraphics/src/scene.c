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

void addLightSource(Scene* scene, GLKVector3 position) {
    LightPoint* newLight = malloc(sizeof(LightPoint));
    newLight->position = position;
    scene->light_count += 1;
    scene->lights = realloc(scene->lights, sizeof(LightPoint*) * scene->light_count);
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

    GLfloat* flatten_array = malloc(3 * scene.light_count * sizeof(GLfloat));
    for (size_t vertex = 0; vertex < scene.light_count; vertex++)
        memcpy(flatten_array + vertex, scene.lights[vertex]->position.v, 3);

    while (head != NULL) {
        updateUniforms(head->model->material, head->model_view, scene.camera, flatten_array, (GLsizei)scene.light_count);
        bindObject(*head->model);
        glDrawArrays(GL_TRIANGLES, 0, head->model->vertices_count);
        head = head->next;
    }
}
