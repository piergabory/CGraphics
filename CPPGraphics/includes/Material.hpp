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
    void setProjectionMatrices(const GLKMatrix4 &modelViewProjection, const GLKMatrix4 &modelView, const GLKMatrix4 &normal);
    inline GLuint programID() const { return m_programID; }
private:
    GLuint m_programID;
    
    GLuint modelViewProjectionMatrixUniform;
    GLuint modelViewMatrixUniform;
    GLuint normalMatrixUniform;
};

class BasicMaterial: public Material {
public:
    BasicMaterial();
private:
    GLKVector3 color = GLKVector3Make(1, 0, 0);
};

class PhongMaterial: public Material {
private:
    float shine;
    float specular;
    float diffuse;
    GLKVector3 color;
    GLuint texture;
};

}

#endif /* Material_hpp */
