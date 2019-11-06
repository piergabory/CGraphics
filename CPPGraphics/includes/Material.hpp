//
//  Material.hpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <string>
#include <GL/glew.h>
#include <GLKit/GLKMath.h>

#include "Shader.hpp"

namespace Gabengine {

class Material {
public:
    Material(const std::string &vertexShader, const std::string &fragmentShader);
protected:
    inline GLuint programID() const { return m_programID; }
private:
    GLuint m_programID;
};

class BasicMaterial: Material {
public:
    BasicMaterial();
private:
    GLuint modelViewProjectionMatrixUniform;
    GLuint modelViewMatrixUniform;
    GLuint normalMatrixUniform;
};

class PhongMaterial: Material {
    private:
    float shine;
    float specular;
    float diffuse;
    GLKVector3 color;
    GLuint texture;
};

}

#endif /* Material_hpp */
