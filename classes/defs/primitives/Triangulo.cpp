#include "../../headers/primitives/Triangulo.h"

Triangulo::Triangulo(int id, BaseMaterial material, Vec3 v1, Vec3 v2, Vec3 v3):Plano(id, material, v1), V1(v1), V2(v2), V3(v3) {
	this->r1 = V2 - V1;
	this->r2 = V3 - V1;
	Vec3 N = r1 * r2;
	this->n = N.norm();
}

void Triangulo::setNormal(Vec3 r1, Vec3 r2) {
	Vec3 N = r1 * r2;
	this->n = N.norm();
}

bool Triangulo::pertence(Vec3 pi) {
	double razao = r1.cross(r2).dot(this->n);
	double c1 = V3.sub(pi).cross(V1.sub(pi)).dot(n) / razao;
	double c2 = V1.sub(pi).cross(V2.sub(pi)).dot(n) / razao;
	double c3 = V2.sub(pi).cross(V3.sub(pi)).dot(n) / razao;
	if (c1 < 0 || c2 < 0 || c3 < 0) return false;
	if (c1 > 1 || c2 > 1 || c3 > 1) return false;
	return (c1 + c2 <= 1);
}

std::optional<LPointGetType> Triangulo::intersecta(Ray raio) {
	std::optional<LPointGetType> ponto = this->Plano::intersecta(raio);
	if (ponto.has_value() && pertence(ponto.value().posContato)) {
		return ponto.value();
	}
	return std::nullopt;
}