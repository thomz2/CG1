#include "../../headers/primitives/Arvore.h"

using namespace std;

Arvore::Arvore(int id, BaseMaterial material, Vec3 translateFactor) : ObjetoComposto(id) {
    Vec3 topoCilindro = translateFactor.add(Vec3(0, 140, 0));
    Vec3 topoCone     = topoCilindro.add(Vec3(0, 200, 0)); 
    BaseMaterial materialCone = BaseMaterial(material.RUGOSIDADE, material.REFLETIVIDADE, Vec3(0, 55.0/255.0, 0), material.M);
    BaseMaterial materialCilindro = BaseMaterial(material.RUGOSIDADE, material.REFLETIVIDADE, Vec3(43.0/255.0, 29.0/255.0, 20.0/255.0), material.M);
    Cilindro* cilindro = new Cilindro(id, {0, 0, 0, 0}, translateFactor, topoCilindro, 30, materialCilindro);
    Cone* cone = new Cone(id, {0, 0, 0, 0}, topoCilindro, topoCone, 120, materialCone); 
    this->subObjetos.push_back(cilindro); // [0] = cilindro
    this->subObjetos.push_back(cone); // [1] = cone
}

int Arvore::printObj(bool printMenu) {
    
    subObjetos[0]->printObj(true); // cilindro
    subObjetos[1]->printObj(true); // cone

    cout << "Deseja fazer algo?" << endl;
    cout << "[0] não" << endl;
    cout << "[1] transladar" << endl;
    cout << "[2] rotacionar" << endl;
    cout << "[3] refletir" << endl;
    int opcao = 0;
    cin >> opcao;
    return opcao; 
}

void Arvore::handleChange(int option) {
    Cilindro* myCilinder = (Cilindro*)subObjetos[0];
    Cone* myCone = (Cone*)subObjetos[1];
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
    {   
        cout << "DIGITE OS VALORES DE X, Y E Z: ";
        cin >> x >> y >> z; 
        Vec3 CilBase = Vec4(myCilinder->Cb).apply(Transformations::translate(x, y, z)).getVec3();
        Vec3 CilTop = Vec4(myCilinder->Ct).apply(Transformations::translate(x, y, z)).getVec3();
        myCilinder->update(CilBase, CilTop);
        Vec3 CoBase = Vec4(myCone->Cb).apply(Transformations::translate(x, y, z)).getVec3();
        Vec3 CoTop  = Vec4(myCone->Vt).apply(Transformations::translate(x, y, z)).getVec3();
        myCone->update(CoBase, CoTop);
        break;
    }
    case 2:
    {
        cout << "DIGITE O EIXO DE ROTACAO (X Y Z): ";
        cin >> x >> y >> z;
        eixo = Vec3(x,y,z);
        cout << "DIGITE O PONTO DE REFERENCIA (X Y Z): ";
        cin >> x >> y >> z;
        ponto = Vec3(x,y,z);
        cout << "DIGITE O ANGULO EM GRAUS: ";
        cin >> x;

        Vec3 CilBase = Vec4(myCilinder->Cb).apply(Transformations::rotateAroundAxisDegrees(x, ponto, eixo)).getVec3();
        Vec3 CilTop = Vec4(myCilinder->Ct).apply(Transformations::rotateAroundAxisDegrees(x, ponto, eixo)).getVec3();
        myCilinder->update(CilBase, CilTop);
        Vec3 CoBase = Vec4(myCone->Cb).apply(Transformations::rotateAroundAxisDegrees(x, ponto, eixo)).getVec3();
        Vec3 CoTop  = Vec4(myCone->Vt).apply(Transformations::rotateAroundAxisDegrees(x, ponto, eixo)).getVec3();
        myCone->update(CoBase, CoTop);

        break;
    }
    case 3:
    {
        cout << "DIGITE UM PONTO QUE PERTENCE AO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 pt = Vec3(x, y, z);
        cout << "DIGITE A NORMAL DO PLANO IMAGINARIO DO ESPELHO (X Y Z): ";
        cin >> x >> y >> z;
        Vec3 normalesp = Vec3(x, y, z);
        
        Vec3 CilBase = Vec4(myCilinder->Cb).apply(Transformations::reflection(normalesp, pt)).getVec3();
        Vec3 CilTop = Vec4(myCilinder->Ct).apply(Transformations::reflection(normalesp, pt)).getVec3();
        myCilinder->update(CilBase, CilTop);
        Vec3 CoBase = Vec4(myCone->Cb).apply(Transformations::reflection(normalesp, pt)).getVec3();
        Vec3 CoTop  = Vec4(myCone->Vt).apply(Transformations::reflection(normalesp, pt)).getVec3();
        myCone->update(CoBase, CoTop);
    }    
    default:
        break;
    }
}