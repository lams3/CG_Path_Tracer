//
// Created by luca on 27/05/18.
//

#ifndef CG_PATH_TRACER_RAYCASTER_H
#define CG_PATH_TRACER_RAYCASTER_H


#include "../math/Ray.h"
#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "../camera/Camera.h"
#include "../renderizable/Renderizable.h"

class RayCaster {

public:
    double near;
    double far;
    Ray ray;

    RayCaster(const double near, const double far, const Ray& ray);

    void set(const Vector3& origin, const Vector3& direction);

    void setFromCamera(const Vector2& coords, Camera camera);

    std::vector<Vector3> intersectObject(Renderizable obj, bool recursive) const;

};


#endif //CG_PATH_TRACER_RAYCASTER_H
