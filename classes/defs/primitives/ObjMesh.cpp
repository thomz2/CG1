#include "../../headers/primitives/ObjMesh.h"
#include "../../headers/primitives/Triangulo.h"
#include <fstream>
#include <sstream>

using namespace std;

ObjMesh::ObjMesh(int id, const string& filepath, const char* filepath2, BaseMaterial material, bool isRGB) : Mesh(id) {
    this->material = material;
    this->textura = new Texture(filepath2, isRGB);
    bool result = readFilePath(filepath);
    if (!result) {
        cout << "ERRO EM LER O PATH NO OBJMESH\n";
    }
}

ObjMesh::ObjMesh(int id, const string& filepath, const char* filepath2, BaseMaterial material) : Mesh(id) {
    this->material = material;
    this->textura = new Texture(filepath2);
    bool result = readFilePath(filepath);
    if (!result) {
        cout << "ERRO EM LER O PATH NO OBJMESH\n";
    }
}

ObjMesh::ObjMesh(int id, const string& filepath, BaseMaterial material) : Mesh(id) {
    this->material = material;
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
            vector<int> uvIndices;

            while (iss >> vertex) {
                size_t pos = vertex.find('/');
                // if (pos != string::npos) {
                //     vertex = vertex.substr(0, pos); // Extract characters before '/'
                // }
                if (pos != string::npos) {

                    int index = stoi(vertex); // Convert to integer and adjust to be 0-based

                    index = (index > 0) ? index - 1 : this->vertices.size() + index;

                    faceIndices.push_back(index);
                }

                // Check if UV coordinate is present
                if (pos != string::npos) {
                    int uvIndex = stoi(vertex.substr(pos + 1));
                    // Convert to 0-based UV index
                    uvIndex = (uvIndex > 0) ? uvIndex - 1 : this->uvs.size() + uvIndex;
                    uvIndices.push_back(uvIndex);
                }
            }
            
            this->gerarTriangulo(faceIndices, uvIndices, this->id, this->material);

            if(faceIndices.size() > 3){
                vector<int> face2Indexes = {faceIndices[0], faceIndices[2], faceIndices[3]};
                vector<int> face2UVIndexes = {uvIndices[0], uvIndices[2], uvIndices[3]};
                this->gerarTriangulo(face2Indexes, face2UVIndexes, this->id, this->material);
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

int ObjMesh::printObj() {
    return Mesh::printObj();
}

void ObjMesh::handleChange(int option) {
	return;
}