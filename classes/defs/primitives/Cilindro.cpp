#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>
#include "../../headers/primitives/Cilindro.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"
#include "../../headers/primitives/Circulo.h"

using namespace std;

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r) : Objeto(id, cor), Cb(Cb), Ct(Ct), r(r) {

    Vec3 dif = Ct - Cb;

    this->h = dif.modulo(); // altura = comprimento do vetor diferença
    this->d = dif.norm();   // direcao = normalizacao do vetor diferença (unitario aqui)

    // TODO: Instanciar faces nos subobjetos
    this->circuloTopo = new Circulo(10000 + id, cor, BaseMaterial(), Ct, dif, r);
    this->circuloBase = new Circulo(10000 + id, cor, BaseMaterial(), Cb, Cb - Ct, r);
};

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r, BaseMaterial material) : Objeto(id, cor, material), Cb(Cb), Ct(Ct), r(r) {

    Vec3 dif = Ct - Cb;

    this->h = dif.modulo(); // altura = comprimento do vetor diferença
    this->d = dif.norm();   // direcao = normalizacao do vetor diferença (unitario aqui)

    // TODO: Instanciar faces nos subobjetos
    this->circuloTopo = new Circulo(10000 + id, cor, material, Ct, dif, r);
    this->circuloBase = new Circulo(10000 + id, cor, material, Cb, Cb - Ct, r);
};

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio) : Objeto(id, cor), Cb(Cb), d(direcao), h(altura), r(raio) {
    this->Ct = Cb.add(direcao.mult(altura));
    this->circuloTopo = new Circulo(10000 + id, cor, material, Ct, Ct - Cb, r);
    this->circuloBase = new Circulo(10000 + id, cor, material, Cb, Cb - Ct, r);    
}

Cilindro::Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio, BaseMaterial material) : Objeto(id, cor, material), Cb(Cb), d(direcao), h(altura), r(raio) {
    this->Ct = Cb.add(direcao.mult(altura));
    this->circuloTopo = new Circulo(10000 + id, cor, material, Ct, Ct - Cb, r);
    this->circuloBase = new Circulo(10000 + id, cor, material, Cb, Cb - Ct, r);    
}

Vec3 Cilindro::getW(Vec3 Pin) {
    return Pin - this->Cb;
}

void Cilindro::update(Vec3 Cb, Vec3 Ct, double raio) {
    this->Cb = Cb;
    this->Ct = Ct;

    Vec3 dif = Ct - Cb;

    this->h = dif.modulo(); // altura = comprimento do vetor diferença
    this->d = dif.norm();   // direcao = normalizacao do vetor diferença (unitario aqui)


    this->circuloTopo->update(Ct, this->d);
    this->circuloBase->update(Cb, dif.mult(-1).norm());
    if (raio != -1) {
        this->circuloTopo->setRaio(raio);
        this->circuloBase->setRaio(raio);
        this->r = raio;
    }

    this->circuloTopo->setNormal(this->d);
    this->circuloBase->setNormal(dif.mult(-1).norm());


}

optional<LPointGetType> Cilindro::intersectaFace(Ray raycaster)
{
    Vec3 dr = raycaster.direcao, w = this->getW(raycaster.Pinicial), dc = this->d;

    double a = dr.dot(dr) - pow((dr.dot(dc)), 2);
    double b = (2 * w.dot(dr)) - ((2 * (w.dot(dc))) * (dr.dot(dc)));
    double c = w.dot(w) - pow(w.dot(dc), 2) - (this->r * this->r);

    double D = pow(b,2) - 4 * a * c;

    if (D < 0) return nullopt;

    // TODO: checar se a distância da projeção pro ponto da base n é negativo nem maior que a altura

    double t1, t2; 
    t1 = (-b - sqrt(D)) / (2*a); t2 = (-b + sqrt(D)) / (2*a);
    Vec3 Po = raycaster.Pinicial;

    Vec3 Pint1 = (dr*t1) + Po;
    Vec3 Pint2 = (dr*t2) + Po;

    Vec3 v1 = Pint1 - Cb;
    Vec3 v2 = Pint2 - Cb;

    Vec3 proj1 = dc * (v1.dot(dc));
    Vec3 proj2 = dc * (v2.dot(dc));

    Vec3 hv1 = v1 - proj1; // vetor h != unidade h
    Vec3 hv2 = v2 - proj2; // vetor h != unidade h

    double dist1 = proj1.modulo();
    double dist2 = proj2.modulo();

    /*
    if (proj1.dot(this->d) > 0 && dist1 < this->h) { // se uma distancia existe
        if (proj2.dot(this->d) > 0 && dist2 < this->h && t2 < t1) // se a outra tbm existe
            return LPointGetType(t2, hv2, Pint2); 
        
        else return LPointGetType(t1, hv1, Pint1); // se apenas a primeira existe
    } 

    else if (proj2.dot(this->d) > 0 && dist2 < this->h) return LPointGetType(t2, hv2, Pint2); // se apenas a segunda existe
    */

    // as duas distancias existem
    if (proj1.dot(this->d) > 0 && dist1 < this->h && proj2.dot(this->d) > 0 && dist2 < this->h) {
        if (t2 < 0 && t1 < 0) {
            return nullopt;
        } else if (t2 < 0) {
            if (t1 >= 0) return LPointGetType(t1, hv1, Pint1);
        } else if (t1 < 0) {
            if (t2 >= 0) return LPointGetType(t2, hv2, Pint2);
        } else {
            return t1 < t2 ? LPointGetType(t1, hv1, Pint1) : LPointGetType(t2, hv2, Pint2);
        }
    } else if (proj1.dot(this->d) > 0 && dist1 < this->h) {
        if (t1 < 0) return nullopt;
        return LPointGetType(t1, hv1, Pint1);
    } else if (proj2.dot(this->d) > 0 && dist2 < this->h) {
        if (t2 < 0) return nullopt;
        return LPointGetType(t2, hv2, Pint2);
    } 

    return nullopt;
}

/*
interseccoes: 

base e face (ver qual ta mais perto)
topo e face (ver qual ta mais perto)
face somente 
base e topo (apenas ver qual ta mais perto, nao precisa calcular face)
*/ 
optional<LPointGetType> Cilindro::intersecta(Ray raycaster) {

    // checar interseccao das bases
    optional<LPointGetType> intersectCT   = this->circuloTopo->intersecta(raycaster);
    optional<LPointGetType> intersectCB   = this->circuloBase->intersecta(raycaster);
    optional<LPointGetType> intersectFace = this->intersectaFace(raycaster);

    optional<LPointGetType> interseccoes[] = {intersectCT, intersectCB, intersectFace};
    optional<LPointGetType> ponto = nullopt;

    for (auto intersec : interseccoes) {
        if (intersec.has_value()) {
            if (ponto.has_value()) {
                if (ponto.value().tint > intersec.value().tint) {
                    ponto = intersec;
                }
            } else {
                ponto = intersec;
            }
        }
    }

    return ponto;

}

int Cilindro::printObj(bool printMenu) {
    cout << "Cilindro ID: " << id << endl;
    cout << "Base Center (Cb): (" << Cb.x << ", " << Cb.y << ", " << Cb.z << ")" << endl;
    cout << "Top Center (Ct): (" << Ct.x << ", " << Ct.y << ", " << Ct.z << ")" << endl;
    cout << "Direction (d): (" << d.x << ", " << d.y << ", " << d.z << ")" << endl;
    cout << "Radius (r): " << r << endl;
    cout << "Height (h): " << h << endl;

    material.printMaterial();

    if (!printMenu) {
        cout << "Deseja fazer algo?" << endl;
        cout << "[0] não" << endl;
        cout << "[1] transladar" << endl;
        cout << "[2] rotacionar" << endl;
        cout << "[3] refletir" << endl;
        cout << "[4] alterar pontos" << endl;
        cout << "[5] alterar raio" << endl;
        cout << "[6] alterar material" << endl;
        int opcao = 0;
        cin >> opcao;
        return opcao; 
    }
    return 0;
}

void Cilindro::handleChange(int option) {
    double x, y, z;
    Vec4 CbNovo;
    Vec4 CtNovo;
    Vec3 ponto;
    Vec3 eixo;
    switch (option)
    {
    case 0:
        break;
    case 1:
        cout << "DIGITE OS VALORES DE X, Y E Z: ";
        cin >> x >> y >> z; 
        CbNovo = Vec4(this->Cb).apply(Transformations::translate(x, y, z));
        CtNovo = Vec4(this->Ct).apply(Transformations::translate(x, y, z));
        // cout << "DEBUG: " << CbNovo.getVec3() << ' ' << CtNovo.getVec3() << endl;
        this->update(CbNovo.getVec3(), CtNovo.getVec3());
        break;
    case 2:
        cout << "DIGITE O EIXO DE ROTACAO (X Y Z): ";
        cin >> x >> y >> z;
        eixo = Vec3(x,y,z);
        cout << "DIGITE O PONTO DE REFERENCIA (X Y Z): ";
        cin >> x >> y >> z;
        ponto = Vec3(x,y,z);
        cout << "DIGITE O ANGULO EM GRAUS: ";
        cin >> x;

        CbNovo = Vec4(this->Cb).apply(
            Transformations::rotateAroundAxisDegrees(x, ponto, eixo));
        CtNovo = Vec4(this->Ct).apply(
            Transformations::rotateAroundAxisDegrees(x, ponto, eixo));

        this->update(CbNovo.getVec3(), CtNovo.getVec3());
        break;
    case 3:
    {
        cout << "DIGITE UM PONTO QUE PERTENCE AO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 pt = Vec3(x, y, z);
        cout << "DIGITE A NORMAL DO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 normalesp = Vec3(x, y, z);
        CbNovo = Vec4(this->Cb).apply(Transformations::reflection(normalesp, pt));
        CtNovo = Vec4(this->Ct).apply(Transformations::reflection(normalesp, pt));
        this->update(CbNovo.getVec3(), CtNovo.getVec3());
        break;

    }
    case 4:
        {

        cout << "DIGITE AS COORDENADAS DE MUNDO DO NOVO CENTRO DA BASE (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 Cbnovo(x, y, z);
        cout << "DIGITE AS COORDENADAS DE MUNDO DO NOVO CENTRO DO TOPO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 Ctnovo(x, y, z);
        this->update(Cbnovo, Ctnovo);
        break;
        }
    case 5:
        {

        cout << "DIGITE O NOVO RAIO: ";
        cin >> x;
        this->update(this->Cb, this->Ct, x);
        break;
        }
    case 6:
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