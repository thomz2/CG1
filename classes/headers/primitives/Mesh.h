#pragma once
#include "Triangulo.h"
#include <vector>
#include "ObjetoComposto.h"
#include "Objeto.h"
#include "../materiais/MaterialTarefa.h"
#include "../materiais/BaseMaterial.h"
#include "../math/Mat4.h"

class Mesh:public ObjetoComposto {
public:
	std::vector<Vec3> vertices;
	std::vector<std::vector<int>> faces;
	std::vector<Vec3> uvs;

	Texture* textura = nullptr;

	Mesh(int id);
	Mesh(int id, vector<Triangulo*> triangulos);
	Mesh(int id, vector<Objeto*> triangulos);
	void gerarTriangulo(std::vector<int> face, int id);
	void gerarTriangulo(std::vector<int> face, int id, BaseMaterial material);
	void gerarTriangulo(std::vector<int> face, std::vector<int> uv, int id, BaseMaterial material);
	void renderizar();
	void applyMatrix(Mat4 matrix);
};