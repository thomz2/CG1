#include "../../headers/primitives/Mesh.h"
#include "../../headers/primitives/Triangulo.h"

Mesh::Mesh(int id) : ObjetoComposto(id) {};

void Mesh::gerarTriangulo(std::vector<int> face, int id) {
	Vec3 v1, v2, v3;
	v1 = vertices[face[0]];
	v2 = vertices[face[1]];
	v3 = vertices[face[2]];
	Triangulo* t = new Triangulo(id, BaseMaterial(), v1, v2, v3);
	this->subObjetos.push_back(t);
}

void Mesh::renderizar() {
	int id = -1;
	for (auto face : this->faces) {
		gerarTriangulo(face, ++id);
	}
}