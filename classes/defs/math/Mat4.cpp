#include "../../headers/math/Mat4.h"
#include "../../headers/math/Vec4.h"
#include <math.h>
#include <iostream>

using namespace std;

Mat4::Mat4(){
    this->matriz = vector<Vec4>(4);
    for(int i=0;i<4;i++){
       setLine(i, Vec4(0, 0, 0, 0));
    }
}

Mat4::Mat4(double matriz[4][4]){
    this->matriz = vector<Vec4>(4);
    for(int i=0;i<4;i++){
        setLine(i, this->matriz[i]);
    }
}

Mat4::Mat4(vector<Vec4> matriz) {
    this->matriz = vector<Vec4>(4);
    for (int i = 0; i < 4; ++i) {
        setLine(i, matriz[i]);
    }
}

void Mat4::setLine(int l, Vec4 vetor) {
    this->matriz[l] = vetor;
}

Mat4 Mat4::add(Mat4 other) {
    Mat4 aux = Mat4();
    for(int i=0;i<4;i++){
        aux.matriz[i] = other.matriz[i].add(this->matriz[i]);
    }
    return aux;
}

Mat4 Mat4::sub(Mat4 other) {
    Mat4 aux = Mat4();
    for(int i=0;i<4;i++){
        aux.matriz[i] = other.matriz[i].sub(this->matriz[i]);
    }
    return aux;
}

Mat4 Mat4::mult(double num) {
    Mat4 aux = Mat4();
    for(int i=0;i<4;i++){
        aux.matriz[i] = this->matriz[i].mult(num);
    }
    return aux;
}

Mat4 Mat4::div(double num) {
    Mat4 aux = Mat4();
    for(int i=0;i<4;i++){
        aux.matriz[i] = this->matriz[i].div(num);
    }
    return aux;
}

Vec4 Mat4::apply(Vec4 vetor) {
    Vec4 aux = Vec4();
 
    aux.x = this->matriz[0].multiplyByTranspose(vetor);
    aux.y = this->matriz[1].multiplyByTranspose(vetor);
    aux.z = this->matriz[2].multiplyByTranspose(vetor);
    aux.w = this->matriz[3].multiplyByTranspose(vetor);

    return aux;
}

Mat4 Mat4::apply(Mat4 matriz) {
    Mat4 aux = Mat4();

    Vec4 col1 = Vec4(matriz.matriz[0].x, matriz.matriz[1].x, matriz.matriz[2].x, matriz.matriz[3].x); 
    Vec4 col2 = Vec4(matriz.matriz[0].y, matriz.matriz[1].y, matriz.matriz[2].y, matriz.matriz[3].y); 
    Vec4 col3 = Vec4(matriz.matriz[0].z, matriz.matriz[1].z, matriz.matriz[2].z, matriz.matriz[3].z); 
    Vec4 col4 = Vec4(matriz.matriz[0].w, matriz.matriz[1].w, matriz.matriz[2].w, matriz.matriz[3].w); 

    for (int i = 0; i < 4; ++i) {
        Vec4 newLine = Vec4();
        Vec4 linhaMult = this->matriz[i];

        newLine.x = linhaMult.multiplyByTranspose(col1);
        newLine.y = linhaMult.multiplyByTranspose(col2);
        newLine.z = linhaMult.multiplyByTranspose(col3);
        newLine.w = linhaMult.multiplyByTranspose(col4);

        aux.matriz[i] = newLine;
    }

    return aux;
}

std::ostream& operator<<(std::ostream& os, const Mat4& other) {
    // return os << '[' << other.x << ' ' << other.y << ' ' << other.z << ']';  
    for (int i = 0; i < 4; ++i) { os << other.matriz[i] << endl; }
    return os;
}