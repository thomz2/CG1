#pragma once
#include "../math/Vec3.h"
#include "../materiais/BaseMaterial.h"
#include <optional>

//TODO: CRIAR DESTRUTOR
class LPointGetType {
public:

    double tint;
    Vec3 normalContato;
    Vec3 posContato;

    std::optional<BaseMaterial> material;

    LPointGetType(double tint, Vec3 normalContato, Vec3 posContato);
    LPointGetType(double tint, Vec3 normalContato, Vec3 posContato, BaseMaterial material);
    LPointGetType();

};

