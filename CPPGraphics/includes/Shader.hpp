//
//  Shader.hpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <map>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include "LoadFile.hpp"

namespace Gabengine {

class Shader {
public:
    inline GLuint identifier() { return m_identifier; }

    // Get singleton
    static const GLuint getVertex(std::string shader);
    static const GLuint getFragment(std::string shader);

    ~Shader();
    Shader(std::string file, GLenum type);

private:
    GLuint m_identifier;

    static std::map<std::string, Shader> vertexShaders;
    static std::map<std::string, Shader> fragmentShaders;
};

}


#endif /* Shader_hpp */
