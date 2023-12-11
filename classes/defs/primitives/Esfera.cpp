#include <SDL2/SDL.h>
#include <math.h>
#include "../../headers/primitives/Esfera.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"
#include "../../headers/materiais/BaseMaterial.h"

using namespace std;

Esfera::Esfera(int id, SDL_Color cor, Vec3 PCentro, double raio, BaseMaterial material) : 
    Objeto(id, cor, material), PCentro(PCentro), raio(raio) {}

Esfera::Esfera(int id, SDL_Color cor, Vec3 PCentro, double raio) : 
    Objeto(id, cor), PCentro(PCentro), raio(raio) {}

// Pin = olho observador
Vec3 Esfera::getW(Vec3 Pin) {
    return Pin - this->PCentro;
}

void Esfera::update(Vec3 c, double raio) {
    if (raio != -1) this->raio = raio;
    this->PCentro = c;
}


// TODO: ajeitar isso aqui depois
optional<LPointGetType> Esfera::intersecta(Ray raycaster) {

    Vec3 w = this->getW(raycaster.Pinicial);

    double a = raycaster.direcao.dot(raycaster.direcao);
    
    double bbarra = w.dot(raycaster.direcao);

    double b = 2 * bbarra;

    double c = w.dot(w) - (this->raio*this->raio);

    // double D = bbarra*bbarra - c;
    double D = pow(b, 2) - 4 * a * c;

    double t1 = (-b - sqrt(D)) / (2*a); 
    double t2 = (-b + sqrt(D)) / (2*a);

    double tint;

    if (D >= 0) {
        tint = (t1 > t2 ? t2 : t1); // distancia mais perto 
        if (t1 < 0 && t2 >= 0) tint = t2;
        if (t2 < 0 && t1 >= 0) tint = t1;
        if (tint < 0) return nullopt;
    } 
    else 
        return nullopt;

    Vec3 direcaodottint = raycaster.direcao * tint; 
    Vec3 Pint           = direcaodottint + raycaster.Pinicial;
    Vec3 normContato    = (Pint - PCentro).norm();

                      // tint, normalcontato, poscontato
    return LPointGetType(tint, normContato, Pint);

}

int Esfera::printObj() {
    std::cout << "Sphere ID: " << id << std::endl;
    std::cout << "Center (PCentro): (" << PCentro.x << ", " << PCentro.y << ", " << PCentro.z << ")" << std::endl;
    std::cout << "Radius (raio): " << raio << std::endl;

    material.printMaterial();

    cout << "Deseja fazer algo?" << endl;
    cout << "[0] não" << endl;
    cout << "[1] transladar" << endl;
    cout << "[2] espelhar" << endl;
    cout << "[3] alterar raio" << endl;
    cout << "[4] alterar material" << endl;
    int opcao = 0;
    cin >> opcao;
    return opcao; 
}

void Esfera::handleChange(int option) {
    double x, y, z;
    Vec4 CbNovo;
    Vec3 ponto;
    Vec3 eixo;
    switch (option)
    {
    case 0:
        break;
    case 1:
        cout << "DIGITE OS VALORES DE X, Y E Z: ";
        cin >> x >> y >> z; 
        CbNovo = Vec4(this->PCentro).apply(Transformations::translate(x, y, z));
        // cout << "DEBUG: " << CbNovo.getVec3() << ' ' << CtNovo.getVec3() << endl;
        this->update(CbNovo.getVec3());
        break;
    case 2:
    {
        cout << "DIGITE UM PONTO QUE PERTENCE AO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 pt = Vec3(x, y, z);
        cout << "DIGITE A NORMAL DO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 normalesp = Vec3(x, y, z);
        CbNovo = Vec4(this->PCentro).apply(Transformations::reflection(normalesp, pt));
        this->update(CbNovo.getVec3());
        break;
    }
    case 3:
        {

        cout << "DIGITE O NOVO RAIO: ";
        cin >> x;
        this->update(this->PCentro, x);
        break;
        }
    case 4:
        {
        int novoMatInd = this->material.offerMaterial();
        Vec3 novoKambiente = this->material.offerColor();
        this->material = this->material.getMaterial(novoMatInd, novoKambiente);
        }
    default:
        break;
    }
	return;
}