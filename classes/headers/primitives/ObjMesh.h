#pragma once
#include "Triangulo.h"
#include <string>
#include <vector>
#include "ObjetoComposto.h"
#include "Mesh.h"
#include "../materiais/BaseMaterial.h"

using namespace std;

class ObjMesh : public Mesh {
    public: 
        ObjMesh(int id, const string& filepath, const char* filepath2);
        ObjMesh(int id, const string& filepath);
        ObjMesh(int id);

        bool readFilePath(const string& filepath);
};