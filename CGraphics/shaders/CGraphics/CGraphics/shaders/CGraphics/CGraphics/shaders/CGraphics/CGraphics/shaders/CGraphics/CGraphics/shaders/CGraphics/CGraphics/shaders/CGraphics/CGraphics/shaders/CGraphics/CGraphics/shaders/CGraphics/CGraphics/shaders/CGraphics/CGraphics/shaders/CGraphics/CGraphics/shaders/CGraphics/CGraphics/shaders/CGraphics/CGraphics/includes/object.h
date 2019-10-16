//
//  object.h
//  CGraphics
//
//  Created by Pierre Gabory on 28/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

#include <string.h>
#include <GL/glew.h>
#include <GLKit/GLKMath.h>

#include "shaders.h"
#include "loader.h"
#include "structs.h"

#include "texture.h"

Object importOBJ(char* filepath, ShaderProgram program);

Object importTexturedOBJ(char* filepath, char* texturepath, ShaderProgram program);

/**
 * Draw Object
 * Renders the object.
 */
void bindObject(Object object);

/**
 * Delete Object
 * Removes the buffers from graphics memory.
 * Does not delete shaders
 *
 * @param object object to delete
 */
void deleteObject(Object object);

#endif /* mesh_h */
