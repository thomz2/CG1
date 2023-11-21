#include "../../headers/types/LPointGetType.h"


LPointGetType::LPointGetType(double tint, Vec3 normalContato, Vec3 posContato) :
    tint(tint), normalContato(normalContato), posContato(posContato), material(std::nullopt) {}

LPointGetType::LPointGetType(double tint, Vec3 normalContato, Vec3 posContato, BaseMaterial material) :
    tint(tint), normalContato(normalContato), posContato(posContato), material(material) {}

LPointGetType::LPointGetType() :
    tint(0), normalContato(Vec3()), posContato(Vec3()), material(std::nullopt) {}