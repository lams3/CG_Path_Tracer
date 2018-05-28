//
// Created by luca on 27/05/18.
//

#ifndef CG_PATH_TRACER_GEOMETRY_H
#define CG_PATH_TRACER_GEOMETRY_H


#include <vector>
#include "../math/Box3.h"
#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include "../math/Ray.h"

class Geometry {

private:
    Box3 boundingBox;

public:
    virtual void applyMatrix(const Matrix4& matrix) = 0;

    virtual void computeBoundingBox() = 0;

    Box3 getBoundingBox() const;

    virtual std::vector<Vector3> intersect(const Ray& ray) const = 0;

};


#endif //CG_PATH_TRACER_GEOMETRY_H
