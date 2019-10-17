//
//  loader.c
//  CGraphics
//
//  Created by Pierre Gabory on 30/09/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "loader.h"

/**
 * Shader source file
 *
 * Returns a string of all the content of a source code file
 *
 * @param path relative file path to the source code
 * @return string content of the source code file
 */
char* loadFile(char* path) {
    FILE* stream = fopen(path, "r");
    if (stream == NULL) {
        fprintf(stderr, "File error: Failed to load file: %s\n", path);
        return NULL;
    }
    fseek(stream, 0L, SEEK_END);
    size_t size = ftell(stream) + 1;
    if (size == 0) {
        fprintf(stderr, "File warning: empty source file: %s\n", path);
    }
    char* source = (char*)malloc(size * sizeof(char));
    rewind(stream);
    fread(source, size, sizeof(char), stream);
    source[size - 1] = '\0';
    return source;
}
