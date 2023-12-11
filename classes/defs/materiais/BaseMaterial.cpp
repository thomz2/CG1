#include "../../headers/materiais/BaseMaterial.h"
#include "../../headers/materiais/Difuso.h"
#include "../../headers/materiais/Madeira.h"
#include "../../headers/materiais/Metalico.h"
#include "../../headers/materiais/Pele.h"
#include "../../headers/materiais/Plastico.h"

using namespace std;

BaseMaterial::BaseMaterial() : RUGOSIDADE(Vec3(1, 1, 1)), REFLETIVIDADE(Vec3(1, 1, 1)), KAMBIENTE(Vec3(1, 1, 1)), M(1) {}

BaseMaterial::BaseMaterial(Vec3 cor255, double M) : RUGOSIDADE(cor255.div(255)), REFLETIVIDADE(cor255.div(255)), KAMBIENTE(cor255.div(255)), M(M) {};

// difusa, especular e ambiente respectivamente
BaseMaterial::BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, Vec3 KAmbiente, double M) : RUGOSIDADE(RUGOSIDADE), REFLETIVIDADE(REFLETIVIDADE), KAMBIENTE(KAmbiente), M(M) {};

BaseMaterial::BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, double M) : RUGOSIDADE(RUGOSIDADE), REFLETIVIDADE(REFLETIVIDADE), KAMBIENTE(Vec3(1, 1, 1)), M(M) {};


Vec3 BaseMaterial::getRugosidade() {
    return RUGOSIDADE;
}

Vec3 BaseMaterial::getRefletividade() {
    return REFLETIVIDADE;
}

Vec3 BaseMaterial::getKAmbiente() {
    return KAMBIENTE;
}

double BaseMaterial::getM() {
    return M;
}

int BaseMaterial::offerMaterial() {
    int option = 0;
    cout << "ESCOLHA O MATERIAL:\n";
    cout << "   [1] DIFUSO\n";
    cout << "   [2] MADEIRA\n";
    cout << "   [3] METALICO\n";
    cout << "   [4] PELE\n";
    cout << "   [5] PLASTICO\n";
    cin >> option;
    return option;
}

Vec3 BaseMaterial::offerColor() {
    Vec3 cor;
    cout << "DIGITE UMA COR EM RGB (R G B): ";
    cin >> cor.x >> cor.y >> cor.z;
    return cor.div(255);
}

BaseMaterial BaseMaterial::getMaterial(int option, Vec3 kambiente) {
    switch (option)
    {
    case 1:
    {

        Difuso difuso = Difuso();
        difuso.KAMBIENTE = kambiente;
        return difuso;
    }
    case 2:
    {

        Madeira madeira = Madeira();
        madeira.KAMBIENTE = kambiente;
        return madeira;
    }
    case 3:
    {
        Metalico metalico = Metalico();
        metalico.KAMBIENTE = kambiente;
        return metalico;
    }
    case 4:
    {

        Pele pele = Pele();
        pele.KAMBIENTE = kambiente;
        return pele;
    } 
    case 5:
    {

        Plastico plastico = Plastico();
        plastico.KAMBIENTE = kambiente;
        return plastico;
    }  
    default:
    {

        return BaseMaterial();
    }
    }
}

void BaseMaterial::printMaterial() {
    std::cout << "MATERIAL: " << std::endl;
    std::cout << "  RUGOSIDADE: (" << RUGOSIDADE.x << ", " << RUGOSIDADE.y << ", " << RUGOSIDADE.z << ")" << std::endl;
    std::cout << "  REFLETIVIDADE: (" << REFLETIVIDADE.x << ", " << REFLETIVIDADE.y << ", " << REFLETIVIDADE.z << ")" << std::endl;
    std::cout << "  KAMBIENTE: (" << KAMBIENTE.x << ", " << KAMBIENTE.y << ", " << KAMBIENTE.z << ")" << std::endl;
    std::cout << "  M: " << M << std::endl;
}