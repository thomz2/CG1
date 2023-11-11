#include "../../headers/math/Vec3.h"
#include <math.h>
#include <iostream>

using namespace std;

Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(Vec3& other) {
    return Vec3(x + other.x, y + other.y, z + other.z);
}
Vec3 Vec3::add(Vec3 other) {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(Vec3& other) {
    return Vec3(x - other.x, y - other.y, z - other.z);
}
Vec3 Vec3::sub(Vec3 other) {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(double num) {
    return Vec3(x * num, y * num, z * num);
}
Vec3 Vec3::mult(double num) {
    return Vec3(x * num, y * num, z * num);
}

// OK
Vec3 Vec3::operator/(double num) {
    return Vec3(x / num, y / num, z / num);
}
Vec3 Vec3::div(double num) {
    return Vec3(x / num, y / num, z / num);
}

// OPERADOR ARROBA
Vec3 Vec3::operator|(Vec3& other) {
    return Vec3(other.x*x,other.y*y,other.z*z);
}

// PROD VETORIAL
Vec3 Vec3::operator*(Vec3& other) {
    return Vec3( ((y*other.z)-(z*other.y)) , ((z*other.x)-(x*other.z)) , ((x*other.y)-(y*other.x)) );
}

// PROD VETORIAL
Vec3 Vec3::cross(Vec3 other) {
    return Vec3(((y * other.z) - (z * other.y)), ((z * other.x) - (x * other.z)), ((x * other.y) - (y * other.x)));
}

// PRODUTO ESCALAR
double Vec3::prodEscalar(Vec3& other) {
    return other.x*x + other.y*y + other.z*z;
}

// PRODUTO ESCALAR
double Vec3::dot(Vec3& other) {
    return other.x*x + other.y*y + other.z*z;
}

// comprimento do vetor ||v||
double Vec3::modulo() {
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

// vetor unitario
Vec3 Vec3::norm() {
    // double mod = this->modulo()
    return *this / this->modulo();
}

// OK
std::ostream& operator<<(std::ostream& os, const Vec3& other) {
    return os << '[' << other.x << ' ' << other.y << ' ' << other.z << ']';  
}

// soma, sub, mult por escalar, div por escalar, op @, prod vetorial, prod escalar, modulo