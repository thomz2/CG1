#include <iostream>

class Vec3 {
    public:
    double x, y, z;

    Vec3();
    Vec3(double x, double y, double z);

    Vec3 operator+(Vec3& other); // OK
    Vec3 operator-(Vec3& other); // OK
    Vec3 operator*(double other);
    Vec3 operator/(double other);
    Vec3 operator|(Vec3& other); // multiplica cada membro por outro e retorna um vetor
    Vec3 operator*(Vec3& other); // prod vetorial
    
    double prodEscalar(Vec3& other); // prod escalar
    double modulo(); // comprimento do vetor

    Vec3 norm();
    
};

std::ostream& operator<<(std::ostream& os, const Vec3& other);