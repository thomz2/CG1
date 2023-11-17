#pragma once
#include "Triangulo.h"
#include <vector>
#include "ObjetoComposto.h"

class Mesh:public ObjetoComposto {
public:
	std::vector<Vec3> vertices;
	std::vector<std::vector<int>> faces;
	Mesh(int id);
	void gerarTriangulo(std::vector<int> face, int id);
	void renderizar();
};