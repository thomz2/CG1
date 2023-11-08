#pragma once
#include "../math/Vec3.h"

//TODO: CRIAR DESTRUTOR
class LPointGetType {
public:

    double tint;
    Vec3 normalContato;
    Vec3 posContato;

    LPointGetType(double tint, Vec3 normalContato, Vec3 posContato);
    LPointGetType();

};

