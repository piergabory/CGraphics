//
//  OBJLoader.hpp
//  CPPGraphics
//
//  Created by Pierre Gabory on 05/11/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef OBJLoader_hpp
#define OBJLoader_hpp

#include "LoadFile.hpp"
#include "Geometry.hpp"

namespace Gabengine {

namespace Loaders {

Geometry* importOBJ(std::string filepath);

}

}
#endif /* OBJLoader_hpp */
