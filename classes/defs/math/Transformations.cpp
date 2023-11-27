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

// TODO: TESTAR
Mat4 Transformations::scaleArroundPoint(double x, double y, double z, Vec3 point) {
    Vec3 p = point;
    return translate(p.x, p.y, p.z).apply(scale(x, y, z).apply(translate(-p.x, -p.y, -p.z)));
}

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

Mat4 Transformations::rotateAroundAxisDegrees(double degrees, Vec3 point, Vec3 axis) {
    double angle = degrees * (pi / 180);
    return rotateAroundAxis(angle, point, axis);
};

// TODO: TESTAR
Mat4 Transformations::rotateAroundAxis(double angle, Vec3 point, Vec3 axis) {
    axis = axis.norm();
    double a = angle, sina = sin(a), cosa = cos(a), opcosa = 1 - cosa, ux = axis.x, uy = axis.y, uz = axis.z;

    Mat4 rotacao = Mat4(
        {
            {cosa + ux*ux*opcosa, ux*uy*opcosa - uz*sina, ux*uz*opcosa + uy*sina, 0},
            {uy*ux*opcosa + uz*sina, cosa + uy*uy*opcosa, uy*uz*opcosa - ux*sina, 0},
            {uz*ux*opcosa - uy*sina, uz*uy*opcosa + ux*sina, cosa + uz*uz*opcosa, 0},
            {0, 0, 0, 1}
        }
    );

    Vec3 p = point;

    return translate(p.x, p.y, p.z).apply(rotacao.apply(translate(-p.x, -p.y, -p.z)));

};