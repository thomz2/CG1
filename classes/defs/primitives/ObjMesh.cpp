#include "../../headers/primitives/ObjMesh.h"
#include "../../headers/primitives/Triangulo.h"
#include <fstream>
#include <sstream>

using namespace std;

ObjMesh::ObjMesh(int id, const string& filepath, const char* filepath2) : Mesh(id) {
    this->textura = new Texture(filepath2);
    bool result = readFilePath(filepath);
    if (!result) {
        cout << "ERRO EM LER O PATH NO OBJMESH\n";
    }
}

ObjMesh::ObjMesh(int id, const string& filepath) : Mesh(id) {
    bool result = readFilePath(filepath);
    if (!result) {
        cout << "ERRO EM LER O PATH NO OBJMESH\n";
    }
}

ObjMesh::ObjMesh(int id) : Mesh(id) {}

bool ObjMesh::readFilePath(const string& filepath) {

    ifstream file(filepath);
    string line;
    int i = 0;
    while (getline(file, line)) {
        ++i;
        istringstream iss(line);
        string type;
        iss >> type;

        //cout << "type = " << type << endl;

        if (type == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            // cout << i << ": v[" << x << " " << y << " " << z << "]\n";
            this->vertices.push_back({x, y, z});
        } else if (type == "f") {
            string vertex;
            vector<int> faceIndices;

            while (iss >> vertex) {
                size_t pos = vertex.find('/');
                if (pos != string::npos) {
                    vertex = vertex.substr(0, pos); // Extract characters before '/'
                }
                int index = stoi(vertex); // Convert to integer and adjust to be 0-based

                index = (index > 0) ? index - 1 : this->vertices.size() + index;

                faceIndices.push_back(index);
            }
            
            this->gerarTriangulo(faceIndices, this->id, BaseMaterial());

            if(faceIndices.size() > 3){
                vector<int> face2Indexes = {faceIndices[0], faceIndices[2], faceIndices[3]};
                this->gerarTriangulo(face2Indexes, this->id);
            }
        } else if (type == "vt") {
            double u, v;
            iss >> u >> v;
            // cout << i << ": vt[" << u << " " << v << "]\n";
            this->uvs.push_back(Vec3(u, v, 0));

        }
    }

    file.close();
    return true;
}