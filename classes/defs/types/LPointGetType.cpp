#include "../../headers/types/LPointGetType.h"

LPointGetType::LPointGetType(double tint, Vec3 normalContato, Vec3 posContato) :
    tint(tint), normalContato(normalContato), posContato(posContato) {}

LPointGetType::LPointGetType() :
    tint(0), normalContato(Vec3()), posContato(Vec3()) {}