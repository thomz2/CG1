#pragma once
#include <iostream>
#include "./Mat4.h"
#include "./Vec3.h"

class Transformations{
    public:
    static constexpr double pi = 3.14159265358979323846;
    static Mat4 scale(double x, double y, double z);
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
};