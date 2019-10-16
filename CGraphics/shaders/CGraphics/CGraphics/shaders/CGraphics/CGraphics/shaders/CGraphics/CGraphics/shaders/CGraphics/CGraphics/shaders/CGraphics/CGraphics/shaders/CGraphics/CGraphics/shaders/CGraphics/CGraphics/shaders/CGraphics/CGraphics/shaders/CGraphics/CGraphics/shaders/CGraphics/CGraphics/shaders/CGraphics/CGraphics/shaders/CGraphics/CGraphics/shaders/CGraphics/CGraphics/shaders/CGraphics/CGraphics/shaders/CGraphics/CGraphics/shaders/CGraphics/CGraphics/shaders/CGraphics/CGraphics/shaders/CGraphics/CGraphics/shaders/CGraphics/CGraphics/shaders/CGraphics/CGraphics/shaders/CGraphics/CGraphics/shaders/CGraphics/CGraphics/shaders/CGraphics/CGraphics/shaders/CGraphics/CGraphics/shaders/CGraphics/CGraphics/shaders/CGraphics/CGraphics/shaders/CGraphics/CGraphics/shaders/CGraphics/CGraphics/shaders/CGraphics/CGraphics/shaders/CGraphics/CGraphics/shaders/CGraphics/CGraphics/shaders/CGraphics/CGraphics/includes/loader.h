//
//  loader.h
//  CGraphics
//
//  Created by Pierre Gabory on 30/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef loader_h
#define loader_h

#include <stdio.h>
#include <stdlib.h>

/**
 * Shader source file
 *
 * Returns a string of all the content of a source code file
 *
 * @param path relative file path to the source code
 * @return string content of the source code file
 */
char* loadFile(char* path);

#endif /* loader_h */
