//
//  texture.h
//  CGraphics
//
//  Created by Pierre Gabory on 16/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef texture_h
#define texture_h

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "structs.h"

GLuint loadTexture(char *png_filename, GLint type);

GLuint loadCubeTexture(char **sides_filenames);

#endif /* texture_h */
