#pragma once
#include "../math/Vec3.h"
#include "Plano.h"
#include "../types/LPointGetType.h"
#include <optional>
#include "../Ray.h"
#include "../materiais/BaseMaterial.h"
#include "./mesh/Texture.h"
#include <math.h>  

class Triangulo : public Plano {
public:
	Vec3 V1, V2, V3, r1, r2;
	Vec3 uv1, uv2, uv3;
	Texture* textura = nullptr;
	Triangulo(int id, BaseMaterial material, Vec3 v1, Vec3 v2, Vec3 v3);
	Triangulo(int id, BaseMaterial material, Texture* textura,  Vec3 v1, Vec3 v2, Vec3 v3, Vec3 uv1, Vec3 uv2, Vec3 uv3);

	void setVs(Vec3 v1, Vec3 v2, Vec3 v3);
	void setUV(Vec3 uv1, Vec3 uv2, Vec3 uv3);
	void setNormal(Vec3 r1, Vec3 r2);
	Vec3 getUV(Vec3 pi);
	std::optional<LPointGetType> intersecta(Ray raio);
	bool pertence(Vec3 pi);

	
};