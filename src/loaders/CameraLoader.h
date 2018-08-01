//
// Created by luca on 25/06/18.
//

#ifndef CG_PATH_TRACER_CAMERALOADER_H
#define CG_PATH_TRACER_CAMERALOADER_H

#include <string>
#include "../core/Camera.h"

class CameraLoader {
public:

    void load(const std::string& path, Camera*& camera);
};


#endif //CG_PATH_TRACER_CAMERALOADER_H
