//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_OBJECTLOADER_H
#define CG_PATH_TRACER_OBJECTLOADER_H


#include <string>
#include "Object3D.h"

class ObjectLoader {
public:
    void load(const std::string& path, Object3D*& object);
};


#endif //CG_PATH_TRACER_OBJECTLOADER_H
