//
//  Mesh.hpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 04/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include "Geometry.hpp"
#include "Material.hpp"
#include "Object.hpp"

namespace Gabengine {

class Mesh : public Object {
public:
    void render(GLKMatrix4 &camera);
    Mesh(Geometry *geometry, Material *material);
    ~Mesh();

private:
    Geometry* geometry;
    Material* material;
};

}

#endif /* Mesh_hpp */
