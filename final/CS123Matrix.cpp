/*!
   @file   CS123Matrix.cpp
   @author Travis Fischer (fisch0920@gmail.com)
   @date   Fall 2008
   
   @brief
      Provides basic functionality for a templated, arbitrarily-sized matrix.
      You will need to fill this file in for the Camtrans assignment.

**/

#include "CS123Algebra.h"
#include <iostream>

//@name Routines which generate specific-purpose transformation matrices
//@{---------------------------------------------------------------------
// @returns the scale matrix described by the vector
Matrix4x4 getScaleMat(const Vector4 &v) {

    return mat4<REAL>(
                v.x,0,0,0,
                0,v.y,0,0,
                0,0,v.z,0,
                0,0,0,1);

}

// @returns the translation matrix described by the vector
Matrix4x4 getTransMat(const Vector4 &v) {
    return mat4<REAL>(
                1, 0, 0, v.x,
                0, 1, 0, v.y,
                0, 0, 1, v.z,
                0, 0, 0, 1
                );
}

// @returns the rotation matrix about the x axis by the specified angle
Matrix4x4 getRotXMat (const REAL radians) {

    return mat4<REAL>(
                1,0,0,0,
                0, cos(radians), -sin(radians), 0,
                0, sin(radians), cos(radians), 0,
                0,0,0,1
                );
}

// @returns the rotation matrix about the y axis by the specified angle
Matrix4x4 getRotYMat (const REAL radians) {
    return mat4<REAL>(
                cos(radians), 0, sin(radians), 0,
                0,1,0,0,
                -sin(radians),0,cos(radians),0,
                0,0,0,1);
}

// @returns the rotation matrix about the z axis by the specified angle
Matrix4x4 getRotZMat (const REAL radians) {
    return mat4<REAL>(
                cos(radians), -sin(radians), 0, 0,
                sin(radians), cos(radians), 0, 0,
                0,0,1,0,
                0,0,0,1);
}

Matrix4x4 getRotMatAboutOrigin(const Vector4 &v, const REAL a) {
    REAL theta = atan2(v.z, v.x);
    REAL phi = -atan2(v.y, sqrt(pow(v.x, 2) + pow(v.z, 2)));
    Matrix4x4 M1 = getRotYMat(theta);
    Matrix4x4 M2 = getRotZMat(phi);
    Matrix4x4 M3 = getRotXMat(a);
    Matrix4x4 iM1 = getInvRotYMat(theta);
    Matrix4x4 iM2 = getInvRotZMat(phi);
    return iM1 * iM2 * M3 * M2 * M1;
}

// @returns the rotation matrix around the vector and point by the specified angle
Matrix4x4 getRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {
    return getTransMat(p) * getRotMatAboutOrigin(v, a) * getTransMat(-p);
}


// @returns the inverse scale matrix described by the vector
Matrix4x4 getInvScaleMat(const Vector4 &v) {
    return getScaleMat(Vector4(1/v.x, 1/v.y, 1/v.z, 1/v.w));
}

// @returns the inverse translation matrix described by the vector
Matrix4x4 getInvTransMat(const Vector4 &v) {
    return getTransMat(-v);
}

// @returns the inverse rotation matrix about the x axis by the specified angle
Matrix4x4 getInvRotXMat (const REAL radians) {
    return getRotXMat(-radians);
}

// @returns the inverse rotation matrix about the y axis by the specified angle
Matrix4x4 getInvRotYMat (const REAL radians) {
    return getRotYMat(-radians);
}

// @returns the inverse rotation matrix about the z axis by the specified angle
Matrix4x4 getInvRotZMat (const REAL radians) {
    return getRotZMat(-radians);
}

// @returns the inverse rotation matrix around the vector and point by the specified angle
Matrix4x4 getInvRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {
    return getRotMat(p, v, -a);
}

Vector3 transformPoint(Matrix4x4 mat, Vector3 vec) {
    Matrix4x4 vecM = Matrix4x4(
                vec.x,0,0,0,
                vec.y,0,0,0,
                vec.z,0,0,0,
                1,0,0,0
                );
    Matrix4x4 res = mat * vecM;
    Vector4 v = Vector4(res.data[0], res.data[4], res.data[8], res.data[12]);
    return Vector3(v.x/v.w, v.y/v.w, v.z/v.w);
}
//@}---------------------------------------------------------------------

