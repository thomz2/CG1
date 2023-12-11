// Interface.h
#pragma once

#include "../math/Vec3.h"

class BaseMaterial {
 
public:
    Vec3 RUGOSIDADE;
    Vec3 REFLETIVIDADE;
    Vec3 KAMBIENTE;
    double M;

    BaseMaterial();
    BaseMaterial(Vec3 cor255, double M);
    BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, Vec3 KAMBIENTE, double M);
    BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, double M);
    

    Vec3 getRugosidade();
    Vec3 getRefletividade();
    Vec3 getKAmbiente();
    double getM();

    int offerMaterial();
    Vec3 offerColor();
    BaseMaterial getMaterial(int option, Vec3 kambiente);
    BaseMaterial getMaterial(int option);

    void printMaterial();

};

