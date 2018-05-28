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

public:

    std::vector<Object3D&> children;
    Object3D* parent;
    Matrix4 matrix;
    Matrix4 matrixWorld;
    Vector3 position;
    Vector3 scale;
    Quaternion quaternion;
    bool visible;

    Object3D();

    void add(const Object3D& obj);

    void remove(const Object3D& obj);

    void applyMatrix(const Matrix4& matrix);

    void applyQuaternion(const Quaternion& q);

    void lookAt(const Vector3& v);

};


#endif //CG_PATH_TRACER_OBJECT3D_H
