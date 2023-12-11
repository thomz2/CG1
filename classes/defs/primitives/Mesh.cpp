#include "../../headers/primitives/Mesh.h"
#include "../../headers/primitives/Triangulo.h"

#include "../../miniball/Seb.h"
typedef double FT;
typedef Seb::Point<FT> Point;
typedef std::vector<Point> PointVector;
typedef Seb::Smallest_enclosing_ball<FT> Miniball;

Miniball getMiniballMesh(vector<Vec3> pontos) {

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

Vec3 Mesh::getMeshCenter() {
	vector<Vec3> pontos;
	for (auto t : this->subObjetos) {
		Triangulo* atual = (Triangulo*)t;
		Vec3 v1, v2, v3;
		v1 = atual->V1;
		v2 = atual->V2;
		v3 = atual->V3;
        pontos.push_back(v1);
        pontos.push_back(v2);
        pontos.push_back(v3);	
	}
	Miniball mb = getMiniballMesh(pontos);
	return Vec3(mb.center_begin()[0], mb.center_begin()[1], mb.center_begin()[2]);
}

Mesh::Mesh(int id) : ObjetoComposto(id) {};

Mesh::Mesh(int id, vector<Triangulo*> triangulos) : ObjetoComposto(id) {
	for (auto t : triangulos) {
		this->subObjetos.push_back(t);
	}
}

Mesh::Mesh(int id, vector<Objeto*> triangulos) : ObjetoComposto(id) {
	for (auto t : triangulos) {
		this->subObjetos.push_back(t);
	}
}

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
	for (auto face : this->faces) {
		gerarTriangulo(face, this->id);
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

int Mesh::printObj() {
	cout << "Mesh ID: " << this->id << endl;
    std::cout << "Mesh Center Point: " << this->getMeshCenter() << std::endl;

    // Print the sizes of vectors
    cout << "Number of Vertices: " << vertices.size() << endl;
    cout << "Number of Faces: " << subObjetos.size() << endl;
    cout << "Number of UVs: " << uvs.size() << endl;

	material.printMaterial();

	cout << "Deseja fazer algo?" << endl;
    cout << "[0] não" << endl;
    cout << "[1] transladar" << endl;
    cout << "[2] escalar" << endl;
    cout << "[3] rotacionar" << endl;
    cout << "[4] cisalhar" << endl;
    cout << "[5] refletir" << endl;
    cout << "[6] alterar material" << endl;
	int opcao = 0;
    cin >> opcao;
    return opcao; 
}

void Mesh::handleChange(int option) {
	double x, y, z;
	Vec3 aux1;
	Vec3 eixo;
	Vec3 ponto;
	switch (option)
	{
	case 1:
        cout << "DIGITE OS VALORES DE X, Y E Z PARA TRANSLADAR: ";
        cin >> x >> y >> z; 
		this->applyMatrix(Transformations::translate(x, y, z));
		break;
	case 2:
        cout << "DIGITE OS VALORES DE X, Y E Z PARA ESCALAR: ";
        cin >> x >> y >> z; 
		cout << "DIGITE UM PONTO DE REFERÊNCIA PARA A ESCALAR: ";
		cin >> aux1.x >> aux1.y >> aux1.z;
		this->applyMatrix(Transformations::scaleArroundPoint(x, y, z, aux1));
		break;
	case 3:
		cout << "DIGITE O EIXO DE ROTACAO (X Y Z): ";
        cin >> x >> y >> z;
        eixo = Vec3(x,y,z);
        cout << "DIGITE O PONTO DE REFERENCIA (X Y Z): ";
        cin >> x >> y >> z;
        ponto = Vec3(x,y,z);
        cout << "DIGITE O ANGULO EM GRAUS: ";
        cin >> x;
		this->applyMatrix(Transformations::rotateAroundAxisDegrees(x, ponto, eixo));
		break;
	case 4:
	{
		double xy, xz, yx, yz, zx, zy;
		cout << "DIGITE OS FATORES DE CISALHAMENTO:\n";
		cout << "Sxy: "; cin >> xy;
		cout << "Sxz: "; cin >> xz;
		cout << "Syx: "; cin >> yx;
		cout << "Syz: "; cin >> yz;
		cout << "Szx: "; cin >> zx;
		cout << "Szy: "; cin >> zy;
		cout << "DIGITE O PONTO DE REFERENCIA (X Y Z): ";
        cin >> x >> y >> z;
        ponto = Vec3(x,y,z);
		this->applyMatrix(Transformations::shearAroundPoint(xy, xz, yx, yz, zx, zy, ponto));
		break;
	}
	case 5: 
	{
		cout << "DIGITE UM PONTO QUE PERTENCE AO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 pt = Vec3(x, y, z);
        cout << "DIGITE A NORMAL DO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 normalesp = Vec3(x, y, z);
		this->applyMatrix(Transformations::reflection(normalesp, pt));
		break;
	}
	case 6:
	{
		int novoMatInd = this->material.offerMaterial();
        this->material = this->material.getMaterial(novoMatInd);
		for (auto t : this->subObjetos) {
			t->material = this->material;
		}
		break;
	}
	default:
		break;
	}

	return;
}