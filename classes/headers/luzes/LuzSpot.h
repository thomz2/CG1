#include "./Luz.h"
#include "./LuzPontual.h"
#pragma once

using namespace std;

class LuzSpot : public LuzPontual {
public:
    double theta;
    Vec3 direcao;
    LuzSpot(Vec3 posicao, Vec3 intensidade, Vec3 direcao, double GRAUS);
    Vec3 calcIntensity(vector<Objeto*> objs, LPointGetType retorno, Ray raycaster, BaseMaterial material);
};