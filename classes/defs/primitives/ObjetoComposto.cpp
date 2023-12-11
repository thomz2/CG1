#include "../../headers/primitives/ObjetoComposto.h"
#include "../../headers/Ray.h"
#include <optional>


using namespace std;

ObjetoComposto::ObjetoComposto(int id) : Objeto(id), subObjetos({}) {}
ObjetoComposto::ObjetoComposto(int id, SDL_Color cor) : Objeto(id, cor), subObjetos({}) {}
ObjetoComposto::ObjetoComposto(int id, SDL_Color cor, BaseMaterial material) : Objeto(id, cor, material), subObjetos({}) {}

optional<LPointGetType> ObjetoComposto::intersecta(Ray ray) {
    optional<LPointGetType> ponto = nullopt;

    for (Objeto* obj : subObjetos) {

        optional<LPointGetType> intersec = obj->intersecta(ray); 
        
        if (intersec.has_value()) {
            if (ponto.has_value()) {
                if (ponto.value().tint > intersec.value().tint) {
                    ponto = intersec;
                    this->cor = obj->cor;
                    this->id = obj->id;
                    this->material = obj->material;
                }
            } else {
                ponto = intersec;
                this->cor = obj->cor;
                this->id = obj->id;
                this->material = obj->material;
            }
        }
    }

    return ponto;

}

int ObjetoComposto::printObj(bool printMenu) {
    return 0;
}

void ObjetoComposto::handleChange(int option) {
	return;
}