#pragma once
#include "../math/Vec3.h"
#include "Plano.h"
#include "../types/LPointGetType.h"
#include <optional>
#include "../Ray.h"
#include "../materiais/BaseMaterial.h"

class Triangulo : public Plano {
public:
	Vec3 V1, V2, V3, r1, r2;
	Triangulo(int id, BaseMaterial material, Vec3 v1, Vec3 v2, Vec3 v3);
	void setNormal(Vec3 r1, Vec3 r2);
	std::optional<LPointGetType> intersecta(Ray raio);
	bool pertence(Vec3 pi);
};