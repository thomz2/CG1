#pragma once 

#include <SDL2/SDL.h>
#include "./ObjetoComposto.h"
#include "./Cone.h"
#include "./Cilindro.h"
#include "../types/LPointGetType.h"
#include <optional>

class Arvore : public ObjetoComposto {

public:

    Arvore(int id, BaseMaterial material, Vec3 translateFactor);

    int printObj(bool printMenu = false) override;
    void handleChange(int option) override;
};