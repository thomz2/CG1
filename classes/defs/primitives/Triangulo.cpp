#include "../../headers/primitives/Triangulo.h"

// struct doisPontos {
// 	Vec3 pontoMundo;
// 	Vec3 uv; // ignorar z
// };



Triangulo::Triangulo(int id, BaseMaterial material, Vec3 v1, Vec3 v2, Vec3 v3):Plano(id, material, v1), V1(v1), V2(v2), V3(v3) {
	this->r1 = V2 - V1;
	this->r2 = V3 - V1;
	Vec3 N = r1 * r2;
	this->n = N.norm();
}

Triangulo::Triangulo(int id, BaseMaterial material, Texture* textura,  Vec3 v1, Vec3 v2, Vec3 v3, Vec3 uv1, Vec3 uv2, Vec3 uv3)
	: Plano(id, material, v1), textura(textura), V1(v1), V2(v2), V3(v3) {
	setUV(uv1, uv2, uv3);
	this->r1 = V2 - V1;
	this->r2 = V3 - V1;
	Vec3 N = r1 * r2;
	this->n = N.norm();
}

void Triangulo::setVs(Vec3 v1, Vec3 v2, Vec3 v3) {
	this->V1 = v1;
	this->V2 = v2;
	this->V3 = v3;
}

void Triangulo::setUV(Vec3 uv1, Vec3 uv2, Vec3 uv3) {
	this->uv1 = uv1;
	this->uv2 = uv2;
	this->uv3 = uv3;
}

void Triangulo::setNormal(Vec3 r1, Vec3 r2) {
	this->r1 = r1;
	this->r2 = r2;
	Vec3 N = r1 * r2;
	this->n = N.norm();
}

Vec3 Triangulo::getUV(Vec3 pi) {
	double razao = r1.cross(r2).dot(this->n);
	double c1 = V3.sub(pi).cross(V1.sub(pi)).dot(n) / razao;
	double c2 = V1.sub(pi).cross(V2.sub(pi)).dot(n) / razao;
	double c3 = V2.sub(pi).cross(V3.sub(pi)).dot(n) / razao;

	Vec3 uvRet = uv1.mult(c3).add(uv2.mult(c1)).add(uv3.mult(c2));
	uvRet.y = 1 - uvRet.y;

	uvRet.x -= floor(uvRet.x);
	uvRet.y -= floor(uvRet.y);

	return uvRet;
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
		if (this->textura == nullptr)
			return ponto.value();

		Vec3 uv = this->getUV(ponto.value().posContato);
		SDL_Color cor = this->textura->sample(uv);
		Vec3 novoKDifuso(
			cor.r,
			cor.g,
			cor.b
		);
		// novoKDifuso = novoKDifuso.norm();
		novoKDifuso = novoKDifuso.div(255);


		// this->material.RUGOSIDADE = novoKDifuso;
		// this->material.KAMBIENTE = novoKDifuso; // TESTE
		BaseMaterial material = BaseMaterial(this->material.RUGOSIDADE, this->material.REFLETIVIDADE, novoKDifuso, this->material.M);
		LPointGetType retorno = LPointGetType(ponto.value().tint, ponto.value().normalContato, ponto.value().posContato, material);
		// cout << retorno.material.value().KAMBIENTE << endl;
		return retorno;
	}
	return std::nullopt;
}

int Triangulo::printObj() {
	std::cout << "Triangulo ID: " << id << std::endl;
    std::cout << "V1: (" << V1.x << ", " << V1.y << ", " << V1.z << ")" << std::endl;
    std::cout << "V2: (" << V2.x << ", " << V2.y << ", " << V2.z << ")" << std::endl;
    std::cout << "V3: (" << V3.x << ", " << V3.y << ", " << V3.z << ")" << std::endl;
    std::cout << "r1: (" << r1.x << ", " << r1.y << ", " << r1.z << ")" << std::endl;
    std::cout << "r2: (" << r2.x << ", " << r2.y << ", " << r2.z << ")" << std::endl;
    
	material.printMaterial();

	return 0;
}

void Triangulo::handleChange(int option) {
	return;
}