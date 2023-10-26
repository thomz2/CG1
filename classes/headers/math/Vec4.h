#pragma once
#include <iostream>
#include "./Vec3.h"

class Mat4;

class Vec4{
    public:
    double x, y, z, w;

    Vec4();
    Vec4(double x, double y, double z, double w);
    Vec4(Vec3 other, double w=1);

    Vec3 getVec3();
    Vec4 add(Vec4 other);
    Vec4 sub(Vec4 other);
    Vec4 mult(double num);
    Vec4 div(double num);
    Vec4 apply(Mat4 matriz);
    double multiplyByTranspose(Vec4 other);
    double modulo();
    Vec4 norm();
};

std::ostream& operator<<(std::ostream& os, const Vec4& other);