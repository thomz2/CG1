#include "./Luz.h"
#include <vector>
#include "../primitives/Objeto.h"
#include "../materiais/BaseMaterial.h"
#pragma once

using namespace std;

class LuzDirecional : public Luz {
public:
    Vec3 direcao;
    LuzDirecional(Vec3 intensidade, Vec3 direcao);
    Vec3 calcIntensity(vector<Objeto*> objs, LPointGetType retorno, Ray raycaster, BaseMaterial material);

};