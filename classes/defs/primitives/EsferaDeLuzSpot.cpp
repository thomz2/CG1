#include "../../headers/primitives/EsferaDeLuzSpot.h"
#include "../../headers/primitives/Esfera.h"

using namespace std;

EsferaDeLuzSpot::EsferaDeLuzSpot(int id, SDL_Color cor, Vec3 Pcentro, double raio, BaseMaterial material, Vec3 intensidade, double graus) 
    : Esfera(id, cor, Pcentro, raio, BaseMaterial(Vec3(0, 0, 0), Vec3(0, 0, 0), material.KAMBIENTE, 1)) {
    this->luzSpot = new LuzSpot(Pcentro.add(Vec3(0, 20*raio + 1, 0)), intensidade, Vec3(0, -1, 0), graus);
}

int EsferaDeLuzSpot::printObj(bool printMenu) {
    Esfera::printObj(true);
    cout << "Spot angle: " << luzSpot->theta * (180/M_PI) << endl;
    cout << "Spot direction: " << luzSpot->direcao << endl;
    cout << "Spot intensity: " << luzSpot->intensidade << endl;

    cout << "Deseja fazer algo?" << endl;
    cout << "[0] não" << endl;
    cout << "[1] transladar" << endl;
    cout << "[2] espelhar" << endl;
    cout << "[3] alterar raio" << endl;
    cout << "[4] alterar material" << endl;
    cout << "[5] alterar abertura da luz" << endl;
    cout << "[6] alterar direcao da luz" << endl;
    cout << "[7] alterar intensidade da luz" << endl;
    int opcao = 0;
    cin >> opcao;
    return opcao; 
}

void EsferaDeLuzSpot::handleChange(int option) {
    double x, y, z;
    Vec4 CbNovo;
    Vec3 ponto;
    Vec3 eixo;
    Vec3 aux;
    switch (option)
    {
    case 5:
        cout << "DIGITE O ANGULO DE ABERTURA EM GRAUS: ";
        cin >> x;
        this->luzSpot->theta = x * (M_PI/180.0);
        break;
    case 6:
        cout << "DIGITE A DIRECAO DA LUZ (X Y Z): ";
        cin >> aux.x >> aux.y >> aux.z;
        this->luzSpot->direcao = aux.norm();
        break;
    case 7:
        cout << "DIGITE A INTENSIDADE DA LUZ (X Y Z): ";
        cin >> aux.x >> aux.y >> aux.z;
        this->luzSpot->intensidade = aux;
        break;
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