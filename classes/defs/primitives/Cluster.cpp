#include "../../headers/primitives/Cluster.h"
#include <optional>

#include "../../miniball/Seb.h"
typedef double FT;
typedef Seb::Point<FT> Point;
typedef std::vector<Point> PointVector;
typedef Seb::Smallest_enclosing_ball<FT> Miniball;

using namespace std;

Miniball getMiniball(vector<Vec3> pontos) {

    PointVector S;
    vector<double> coords(3);
    
    for (int i = 0; i < pontos.size(); ++i) {
        coords[0] = pontos[i].x;
        coords[1] = pontos[i].y;
        coords[2] = pontos[i].z;
        S.push_back(Point(3, coords.begin()));
    }

    return Miniball(3, S);
}

Cluster::Cluster(Mesh* malha, int depth, bool first) : ObjetoComposto(malha->id) {
    
    if (first) {
        this->malha = malha;
    }

    vector<Vec3> pontos;
	for (auto triangulo : malha->subObjetos) {
        Triangulo* atual = (Triangulo*)triangulo;
		Vec3 v1, v2, v3;
		v1 = atual->V1;
		v2 = atual->V2;
		v3 = atual->V3;
        pontos.push_back(v1);
        pontos.push_back(v2);
        pontos.push_back(v3);
    }
    Miniball mb = getMiniball(pontos);
    this->fronteira = new Esfera(
        malha->id, 
        {0, 0, 0, 0}, 
        Vec3(mb.center_begin()[0], mb.center_begin()[1], mb.center_begin()[2]),    
        mb.radius()
    );
        
    if (depth != 0){
        if(malha->subObjetos.size() > 5){
            unsigned long long middleIndex = malha->subObjetos.size() / 2;
        
            vector<Objeto*> sub_vector1(malha->subObjetos.begin(), malha->subObjetos.begin() + middleIndex);
            vector<Objeto*> sub_vector2(malha->subObjetos.begin() + middleIndex, malha->subObjetos.end());

            this->subObjetos.push_back(new Cluster(new Mesh(malha->id, sub_vector1), depth-1));
            this->subObjetos.push_back(new Cluster(new Mesh(malha->id, sub_vector2), depth-1));
        }
        else
            this->subObjetos.push_back(malha);
    }
    else
        this->subObjetos.push_back(malha);
};


void Cluster::initializeCluster(Mesh* malha, int depth, bool first) {
    this->id = malha->id;

    if (first) {
        this->malha = malha;
    }

    vector<Vec3> pontos;
    for (auto triangulo : malha->subObjetos) {
        Triangulo* atual = (Triangulo*)triangulo;
        Vec3 v1, v2, v3;
        v1 = atual->V1;
        v2 = atual->V2;
        v3 = atual->V3;
        pontos.push_back(v1);
        pontos.push_back(v2);
        pontos.push_back(v3);
    }
    Miniball mb = getMiniball(pontos);
    this->fronteira = new Esfera(
        malha->id, 
        {0, 0, 0, 0}, 
        Vec3(mb.center_begin()[0], mb.center_begin()[1], mb.center_begin()[2]),    
        mb.radius()
    );

    if (depth != 0) {
        if(malha->subObjetos.size() > 5){
            unsigned long long middleIndex = malha->subObjetos.size() / 2;
        
            vector<Objeto*> sub_vector1(malha->subObjetos.begin(), malha->subObjetos.begin() + middleIndex);
            vector<Objeto*> sub_vector2(malha->subObjetos.begin() + middleIndex, malha->subObjetos.end());

            this->subObjetos.push_back(new Cluster(new Mesh(malha->id, sub_vector1), depth-1));
            this->subObjetos.push_back(new Cluster(new Mesh(malha->id, sub_vector2), depth-1));
        }
        else {
            this->subObjetos.push_back(malha);
        }
    }
    else {
        this->subObjetos.push_back(malha);
    }
}


std::optional<LPointGetType> Cluster::intersecta(Ray raio) {
    if (fronteira == nullptr) return this->ObjetoComposto::intersecta(raio);
    optional<LPointGetType> interseccao = fronteira->intersecta(raio);
    // return interseccao;
    if (!interseccao.has_value()) return nullopt;
    return this->ObjetoComposto::intersecta(raio);
};

int Cluster::printObj() {
    if (this->malha != nullptr)
        return this->malha->printObj();
    return 0;
}

void Cluster::handleChange(int option) {
    if (this->malha != nullptr) {
        this->malha->handleChange(option);
        this->subObjetos.clear();
        this->initializeCluster(this->malha, 20000, false);
    }
	return;
}