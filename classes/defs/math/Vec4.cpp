#include "../../headers/math/Vec4.h"
#include "../../headers/math/Mat4.h"
#include <math.h>
#include <iostream>

using namespace std;

Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
Vec4::Vec4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
Vec4::Vec4(Vec3 other, double w) : x(other.x), y(other.y), z(other.z), w(w) {}

Vec3 Vec4::getVec3() {
    return Vec3(x, y, z);
}

Vec4 Vec4::add(Vec4 other) {
    return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vec4 Vec4::sub(Vec4 other) {
    return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vec4 Vec4::mult(double num) {
    return Vec4(x * num, y * num, z * num, w * num);
}

Vec4 Vec4::div(double num) {
    return Vec4(x / num, y / num, z / num, w / num);
}

Vec4 Vec4::apply(Mat4 matriz) {
    Vec4 aux = Vec4();

    aux.x = matriz.matriz[0].multiplyByTranspose(*this);
    aux.y = matriz.matriz[1].multiplyByTranspose(*this);
    aux.z = matriz.matriz[2].multiplyByTranspose(*this);
    aux.w = matriz.matriz[3].multiplyByTranspose(*this);

    return aux;
}

// MULTIPLICACAO DE UM VETOR PELO TRANSPOSTO DE OUTRO (FUNCIONANDO)
double Vec4::multiplyByTranspose(Vec4 other) {
    return other.x*x + other.y*y + other.z*z + other.w*w;
}

double Vec4::modulo() {
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2)+pow(w,2));
}

Vec4 Vec4::norm() {
    return this->div(this->modulo());
}

std::ostream& operator<<(std::ostream& os, const Vec4& other) {
    return os << '[' << other.x << ' ' << other.y << ' ' << other.z << ' ' << other.w << ']';  
}
