#pragma once
#include <iostream>
#include "./Mat4.h"
#include "./Vec3.h"

class Transformations{
    public:
    static constexpr double pi = 3.14159265358979323846;
    static Mat4 scale(double x, double y, double z);
    static Mat4 scaleArroundPoint(double x, double y, double z, Vec3 point);
    static Mat4 translate(double x, double y, double z);
    static Mat4 rotateXByDegree(double angulo);
    static Mat4 rotateXByRadian(double angulo_radiano);
    static Mat4 rotateYByDegree(double angulo);
    static Mat4 rotateYByRadian(double angulo_radiano);
    static Mat4 rotateZByDegree(double angulo);
    static Mat4 rotateZByRadian(double angulo_radiano);
    static Mat4 rotateXAroundPoint(double angle, Vec3 point);
    static Mat4 rotateYAroundPoint(double angle, Vec3 point);
    static Mat4 rotateZAroundPoint(double angle, Vec3 point);
    static Mat4 rotateXAroundPointDegrees(double degrees, Vec3 point);
    static Mat4 rotateYAroundPointDegrees(double degrees, Vec3 point);
    static Mat4 rotateZAroundPointDegrees(double degrees, Vec3 point);
    static Mat4 rotateAroundAxisDegrees(double degrees, Vec3 point, Vec3 axis);
    static Mat4 rotateAroundAxis(double angle, Vec3 point, Vec3 axis);
    static Mat4 shearX(double y, double z);
    static Mat4 shearY(double x, double z);
    static Mat4 shearZ(double x, double y);
    static Mat4 shear(double xy = 0, double xz = 0, double yx = 0, double yz = 0, double zx = 0, double zy = 0);
    static Mat4 shearAroundPoint(double xy = 0, double xz = 0, double yx = 0, double yz = 0, double zx = 0, double zy = 0, Vec3 point = Vec3(0, 0, 0));
    static Mat4 reflection(Vec3 normal, Vec3 point); 
};