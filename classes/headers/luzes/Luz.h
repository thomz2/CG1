#include "../math/Vec3.h"
#include <vector>
#include "../primitives/Objeto.h"
#include "../materiais/BaseMaterial.h"
#include "../Ray.h"
#include "../types/LPointGetType.h"
#pragma once

using namespace std;

class Luz {

public:
    Vec3 posicao;
    Vec3 intensidade;

    Luz(Vec3 posicao, Vec3 intensidade);
    virtual Vec3 calcIntensity(vector<Objeto*> objs, LPointGetType retorno, Ray raycaster, BaseMaterial material) = 0;
};