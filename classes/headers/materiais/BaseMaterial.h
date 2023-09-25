// Interface.h
#pragma once

#include "../math/Vec3.h"

class BaseMaterial {
 
private:
    Vec3 RUGOSIDADE;
    Vec3 REFLETIVIDADE;
    double M;

public:
    BaseMaterial();
    BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, double M);
    
    Vec3 getRugosidade();
    Vec3 getRefletividade();
    double getM();

};

