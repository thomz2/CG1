#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <optional>

#include "../Ray.h"
#include "./Objeto.h"
#include "../materiais/BaseMaterial.h"

class ObjetoComposto : public Objeto {

public:

    std::vector<Objeto*> subObjetos;

    ObjetoComposto(int id);
    ObjetoComposto(int id, SDL_Color cor);
    ObjetoComposto(int id, SDL_Color cor, BaseMaterial material);
    
    std::optional<LPointGetType> intersecta(Ray ray);

    void printObj() override;
};