//
//  LoadFile.cpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 05/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "LoadFile.hpp"

namespace Gabengine {

namespace Loaders {

std::string loadFile(const std::string &path) {
    FILE* stream = std::fopen(path.c_str(), "r");
    if (stream == nullptr) {
        std::cerr << "File error: Failed to load file:" << path << "\n";
        return "";
    }
    fseek(stream, 0L, SEEK_END);
    size_t size = ftell(stream) + 1;
    if (size == 0) {
        std::cerr << "File warning: empty source file::" << path << "\n";
        return "";
    }
    char* source = new char[size];
    rewind(stream);
    fread(source, size, sizeof(char), stream);
    source[size - 1] = '\0';

    std::string string(source);
    delete[] source;

    return string;
}

}

}
