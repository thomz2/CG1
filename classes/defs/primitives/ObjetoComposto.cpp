#include "../../headers/primitives/ObjetoComposto.h"
#include "../../headers/Ray.h"

ObjetoComposto::ObjetoComposto(int id) : Objeto(id), subObjetos({}) {}
ObjetoComposto::ObjetoComposto(int id, SDL_Color cor) : Objeto(id, cor), subObjetos({}) {}
ObjetoComposto::ObjetoComposto(int id, SDL_Color cor, BaseMaterial material) : Objeto(id, cor, material), subObjetos({}) {}
