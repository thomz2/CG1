#include "../../headers/math/Transformations.h"
#include <math.h>
#include <iostream>

using namespace std;

Mat4 Transformations::scale(double x, double y, double z) {
    Mat4 matriz = Mat4(
        {
            {x, 0, 0, 0},
            {0, y, 0, 0},
            {0, 0, z, 0},
            {0, 0, 0, 1}
        }
    );
    return matriz;
};

Mat4 Transformations::translate(double x, double y, double z) {
    return Mat4(
        {{1,0,0,x}, 
        {0,1,0,y}, 
        {0,0,1,z}, 
        {0,0,0,1}}
    );
};

Mat4 Transformations::rotateXByRadian(double angulo_radiano){
    return Mat4(
        {{1,0,0,0}, 
        {0,cos(angulo_radiano),-sin(angulo_radiano),0}, 
        {0,sin(angulo_radiano),cos(angulo_radiano),0}, 
        {0,0,0,1}}
    );
}

Mat4 Transformations::rotateXByDegree(double angulo){
    double angulo_radiano = angulo * (pi / 180);
    return Mat4(
        {{1,0,0,0}, 
        {0,cos(angulo_radiano),-sin(angulo_radiano),0}, 
        {0,sin(angulo_radiano),cos(angulo_radiano),0}, 
        {0,0,0,1}}
    );
}

Mat4 Transformations::rotateYByRadian(double angulo_radiano){
    return Mat4(
        {{cos(angulo_radiano),0,sin(angulo_radiano),0}, 
        {0,1,0,0}, 
        {-sin(angulo_radiano),0,cos(angulo_radiano),0}, 
        {0,0,0,1}}
    );
}

Mat4 Transformations::rotateYByDegree(double angulo){
    double angulo_radiano = angulo * (pi / 180);
    return Mat4(
        {{cos(angulo_radiano),0,sin(angulo_radiano),0}, 
        {0,1,0,0}, 
        {-sin(angulo_radiano),0,cos(angulo_radiano),0}, 
        {0,0,0,1}}
    );
}

Mat4 Transformations::rotateZByRadian(double angulo_radiano){
    return Mat4(
        {{cos(angulo_radiano),-sin(angulo_radiano),0,0}, 
        {sin(angulo_radiano),cos(angulo_radiano),0,0}, 
        {0,0,1,0}, 
        {0,0,0,1}}
    );
}

Mat4 Transformations::rotateZByDegree(double angulo){
    double angulo_radiano = angulo * (pi / 180);
    return Mat4(
        {{cos(angulo_radiano),-sin(angulo_radiano),0,0}, 
        {sin(angulo_radiano),cos(angulo_radiano),0,0}, 
        {0,0,1,0}, 
        {0,0,0,1}}
    );
}

Mat4 Transformations::rotateXAroundPoint(double angle, Vec3 point) {
    double x = point.x, y = point.y, z = point.z;
    return Transformations::translate(x, y, z).apply(Transformations::rotateXByRadian(angle)).apply(Transformations::translate(-x, -y, -z));
};

Mat4 Transformations::rotateYAroundPoint(double angle, Vec3 point) {
    double x = point.x, y = point.y, z = point.z;
    return Transformations::translate(x, y, z).apply(Transformations::rotateYByRadian(angle)).apply(Transformations::translate(-x, -y, -z));
};

Mat4 Transformations::rotateZAroundPoint(double angle, Vec3 point) {
    double x = point.x, y = point.y, z = point.z;
    return Transformations::translate(x, y, z).apply(Transformations::rotateZByRadian(angle)).apply(Transformations::translate(-x, -y, -z));
};

Mat4 Transformations::rotateXAroundPointDegrees(double degrees, Vec3 point) {
    double angle = degrees * (pi / 180);
    double x = point.x, y = point.y, z = point.z;
    return Transformations::translate(x, y, z).apply(Transformations::rotateXByRadian(angle)).apply(Transformations::translate(-x, -y, -z));
};

Mat4 Transformations::rotateYAroundPointDegrees(double degrees, Vec3 point) {
    double angle = degrees * (pi / 180);
    double x = point.x, y = point.y, z = point.z;
    return Transformations::translate(x, y, z).apply(Transformations::rotateYByRadian(angle)).apply(Transformations::translate(-x, -y, -z));
};

Mat4 Transformations::rotateZAroundPointDegrees(double degrees, Vec3 point) {
    double angle = degrees * (pi / 180);
    double x = point.x, y = point.y, z = point.z;
    return Transformations::translate(x, y, z).apply(Transformations::rotateZByRadian(angle)).apply(Transformations::translate(-x, -y, -z));
};
