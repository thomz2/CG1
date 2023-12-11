#include <SDL2/SDL.h>
#include <math.h>
#include "../../headers/primitives/Cone.h"
#include "../../headers/primitives/Objeto.h"
#include "../../headers/Ray.h"
#include "../../headers/math/Vec3.h"

using namespace std;

Cone::Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r) : Objeto(id, cor), Cb(Cb), Vt(Vt), r(r) {
    
    Vec3 dif = Vt - Cb;
    
    // mesma coisa do cilindro
    this->h = dif.modulo();
    this->d = dif.norm();
    
    // TODO: Instanciar faces nos subobjetos
    this->base = new Circulo(10000 + id, cor, BaseMaterial(), Cb, Cb.sub(Vt).norm(), r);

}

Cone::Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 Vt, double r, BaseMaterial material) : Objeto(id, cor, material), Cb(Cb), Vt(Vt), r(r) {
    
    Vec3 dif = Vt - Cb;
    
    // mesma coisa do cilindro
    this->h = dif.modulo();
    this->d = dif.norm();
    
    // TODO: Instanciar faces nos subobjetos
    this->base = new Circulo(10000 + id, cor, material, Cb, Cb.sub(Vt).norm(), r);
}

Cone::Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio) : Objeto(id, cor), Cb(Cb), d(direcao), h(altura), r(raio){
    this->Vt = Cb.add(direcao.mult(altura));
    this->d = direcao;
    this->base = new Circulo(10000+ id, cor, BaseMaterial(), Cb, Cb.sub(Vt).norm(), raio);
}

Cone::Cone(int id, SDL_Color cor, Vec3 Cb, Vec3 direcao, double altura, double raio, BaseMaterial material) : Objeto(id, cor, material), Cb(Cb), d(direcao), h(altura), r(raio) {
    this->Vt = Cb.add(direcao.mult(altura));
    this->d = direcao;
    this->base = new Circulo(10000 + id, cor, material, Cb, Cb.sub(Vt).norm(), raio);
}

void Cone::update(Vec3 Cb, Vec3 Vt, double raio) {
    this->Cb = Cb;
    this->Vt = Vt;

    Vec3 dif = Vt - Cb;

    this->h = dif.modulo(); // altura = comprimento do vetor diferença
    this->d = dif.norm();   // direcao = normalizacao do vetor diferença (unitario aqui)


    this->base->update(Cb, dif.mult(-1).norm());
    if (raio != -1) {
        this->base->setRaio(raio);
        this->r = raio;
    }

    this->base->setNormal(dif.mult(-1).norm());

}

optional<LPointGetType> Cone::intersectaFace(Ray raycaster) {
    Vec3 v = this->Vt.sub(raycaster.Pinicial);
    Vec3 d = raycaster.direcao;
    Vec3 n = this->d;

    double generatrix2 = this->h*this->h + this->r*this->r; //sqrt()^2
    double cos2theta = this->h*this->h / generatrix2; //cos2theta = (altura / geratriz)^2
    

    double fA = pow((d.dot(n)), 2) - (d.dot(d)) * cos2theta;
    double fB = (v.dot(d))*cos2theta - (v.dot(n))*(d.dot(n));
    double fC = pow((v.dot(n)), 2) - v.dot(v)*cos2theta;
    double fD = fB*fB - fA*fC; //delta 

    
    if (fD < 0) return nullopt;

    double t;
    Vec3 contactPosition;
    double contactProjectionMag;
    Vec3 contactProjectionLength;
    //existe pelo menos uma raiz => contato    
    if (fD == 0) { //raiz unica
        t = -fB/fA;
    } else {
        double t1 = (-fB + sqrt(fD)) / (fA);
        double t2 = (-fB - sqrt(fD)) / (fA);
        
        if (t1 > t2) std::swap(t1, t2);

        if (t1 < 0) {
            t1 = t2; // if t0 is negative, let's use t1 instead
            if (t1 < 0) return nullopt; // both t0 and t1 are negative
        }
        t = t1;

        contactPosition = raycaster.Pinicial.add(raycaster.direcao*t);
        contactProjectionMag = (contactPosition.sub(Cb)).dot(n);

        if ((contactProjectionMag < 0) || (contactProjectionMag) > this->h) {
            t = t2;
        }
    }

    contactPosition = raycaster.Pinicial.add(raycaster.direcao*t);
    contactProjectionMag = (contactPosition.sub(Cb)).dot(n);
    if ((contactProjectionMag < 0) || (contactProjectionMag) > this->h) {
        return nullopt;
    }

    Vec3 contactToVertex = Cb.add( (n*this->h) - contactPosition);
    
    Vec3 projetionPoint = Cb.add(n*contactProjectionMag);
    Vec3 insideVec = contactPosition - projetionPoint;
    Vec3 cross = ((contactToVertex).cross(insideVec)).norm();
    Vec3 normal = ((cross).cross(contactToVertex)).norm();

    return LPointGetType(t, normal, contactPosition);



}

optional<LPointGetType> Cone::intersecta(Ray raycaster) {

    optional<LPointGetType> intersectCB = this->base->intersecta(raycaster);
    optional<LPointGetType> intersectFace = this->intersectaFace(raycaster);

    optional<LPointGetType> interseccoes[] = {intersectFace, intersectCB};
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

int Cone::printObj() {
    std::cout << "Cone ID: " << id << std::endl;
    std::cout << "Base Center (Cb): (" << Cb.x << ", " << Cb.y << ", " << Cb.z << ")" << std::endl;
    std::cout << "Vertex Top (Vt): (" << Vt.x << ", " << Vt.y << ", " << Vt.z << ")" << std::endl;
    std::cout << "Direction (d): (" << d.x << ", " << d.y << ", " << d.z << ")" << std::endl;
    std::cout << "Radius (r): " << r << std::endl;
    std::cout << "Height (h): " << h << std::endl;

    material.printMaterial();

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

void Cone::handleChange(int option) {
	double x, y, z;
    Vec4 CbNovo;
    Vec4 VtNovo;
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
        VtNovo = Vec4(this->Vt).apply(Transformations::translate(x, y, z));
        // cout << "DEBUG: " << CbNovo.getVec3() << ' ' << VtNovo.getVec3() << endl;
        this->update(CbNovo.getVec3(), VtNovo.getVec3());
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
        VtNovo = Vec4(this->Vt).apply(
            Transformations::rotateAroundAxisDegrees(x, ponto, eixo));

        this->update(CbNovo.getVec3(), VtNovo.getVec3());
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
        VtNovo = Vec4(this->Vt).apply(Transformations::reflection(normalesp, pt));
        this->update(CbNovo.getVec3(), VtNovo.getVec3());
        break;

    }
    case 4:
        {

        cout << "DIGITE AS COORDENADAS DE MUNDO DO NOVO CENTRO DA BASE (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 Cbnovo(x, y, z);
        cout << "DIGITE AS COORDENADAS DE MUNDO DO NOVO CENTRO DO TOPO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 Vtnovo(x, y, z);
        this->update(Cbnovo, Vtnovo);
        break;
        }
    case 5:
        {

        cout << "DIGITE O NOVO RAIO: ";
        cin >> x;
        this->update(this->Cb, this->Vt, x);
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