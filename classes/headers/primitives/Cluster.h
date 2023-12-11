#pragma once

#include <SDL2/SDL.h>
#include "./ObjetoComposto.h"
#include "./Esfera.h"
#include "./Mesh.h"
#include "./Triangulo.h"
#include "../types/LPointGetType.h"
#include <optional>

class Cluster : public ObjetoComposto {

public: 

    Mesh* malha;
    Esfera* fronteira = nullptr;
    Cluster(Mesh* malha, int depth, bool first = false);
    void initializeCluster(Mesh* malha, int depth, bool first = false);
    std::optional<LPointGetType> intersecta(Ray ray) override;
    int printObj(bool printMenu = false) override;
    void handleChange(int option) override;

};