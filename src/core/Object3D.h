//
// Created by luca on 26/05/18.
//

#ifndef CG_PATH_TRACER_OBJECT3D_H
#define CG_PATH_TRACER_OBJECT3D_H


#include <vector>
#include "../math/Matrix4.h"
#include "../math/Vector3.h"
#include "../math/Quaternion.h"
#include "../math/Matrix4.h"

class Object3D {
    std::vector<Object3D&> children;
    Object3D* parent;
    Matrix4 matrix;
    Matrix4 matrixWorld;
    Vector3 position;
    Vector3 scale;
    Quaternion quaternion;
    bool visible;

    void add(const Object3D&, const Object3D&...);

    void remove(const Object3D&, const Object3D&...);

    void applyMatrix(const Matrix4&);

    void applyQuaternion(const Quaternion&);

    void lookAt(const Vector3&);

};


#endif //CG_PATH_TRACER_OBJECT3D_H
