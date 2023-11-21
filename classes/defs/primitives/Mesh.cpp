#include "../../headers/primitives/Mesh.h"
#include "../../headers/primitives/Triangulo.h"

Mesh::Mesh(int id) : ObjetoComposto(id) {};

void Mesh::gerarTriangulo(std::vector<int> face, int id) {
	Vec3 v1, v2, v3;
	v1 = vertices[face[0]];
	v2 = vertices[face[1]];
	v3 = vertices[face[2]];
	Triangulo* t = new Triangulo(id, MaterialTarefa(), v1, v2, v3);
	this->subObjetos.push_back(t);
}

void Mesh::gerarTriangulo(std::vector<int> face, int id, BaseMaterial material) {
	Vec3 v1, v2, v3;
	v1 = vertices[face[0]];
	v2 = vertices[face[1]];
	v3 = vertices[face[2]];
	Triangulo* t = new Triangulo(id, material, v1, v2, v3);
	this->subObjetos.push_back(t);
}

void Mesh::gerarTriangulo(std::vector<int> face, std::vector<int> uv, int id, BaseMaterial material) {
	Vec3 v1, v2, v3;
	v1 = vertices[face[0]];
	v2 = vertices[face[1]];
	v3 = vertices[face[2]];

	Triangulo* t = nullptr;

	if (this->textura == nullptr) {

		t = new Triangulo(id, material, v1, v2, v3);
		
	} else {

		Vec3 uv1, uv2, uv3;
		uv1 = this->uvs[uv[0]];
		uv2 = this->uvs[uv[1]];
		uv3 = this->uvs[uv[2]];
		// cout << "TESTE UV1: " << uv1 << endl;
		t = new Triangulo(id, material, this->textura, v1, v2, v3, uv1, uv2, uv3);

	}

	this->subObjetos.push_back(t);
}

void Mesh::renderizar() {
	int id = -1;
	for (auto face : this->faces) {
		gerarTriangulo(face, ++id);
	}
}

void Mesh::applyMatrix(Mat4 matrix) {
	for (auto triangulo : this->subObjetos) {
		Triangulo* atual = (Triangulo*)triangulo;
		Vec4 v1, v2, v3;
		v1 = Vec4(atual->V1).apply(matrix);
		v2 = Vec4(atual->V2).apply(matrix);
		v3 = Vec4(atual->V3).apply(matrix);
		
		Vec3 V1 = v1.getVec3();
		Vec3 V2 = v2.getVec3();
		Vec3 V3 = v3.getVec3();

		atual->setVs(V1, V2, V3);
		atual->Ppi = V1;

		Vec3 r1 = V2.sub(V1);
		Vec3 r2 = V3.sub(V1);
		atual->setNormal(r1, r2);
	}
}
