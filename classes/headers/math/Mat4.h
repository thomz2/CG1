#pragma once
#include <iostream>
#include <vector>
#include "./Vec4.h"

using namespace std;

class Mat4{
    public:
    vector<Vec4> matriz;

    Mat4();
    Mat4(double matriz[4][4]);
    Mat4(vector<Vec4> matriz);

    void setLine(int l, Vec4 vetor);
    Mat4 add(Mat4 other);
    Mat4 sub(Mat4 other);
    Mat4 mult(double value);
    Mat4 div(double value);
    Vec4 apply(Vec4 vetor);
    Mat4 apply(Mat4 matriz);
};

std::ostream& operator<<(std::ostream& os, const Mat4& other);
