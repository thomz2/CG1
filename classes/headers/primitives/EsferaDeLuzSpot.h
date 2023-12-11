#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "../math/Vec4.h"
#include "../math/Transformations.h"
#include "../luzes/LuzSpot.h"
#include "./Esfera.h"
#include "../Ray.h"
#include "../materiais/BaseMaterial.h"
#include "../types/LPointGetType.h"

class EsferaDeLuzSpot : public Esfera {
    public:
    LuzSpot* luzSpot;
    EsferaDeLuzSpot(int id, SDL_Color cor, Vec3 Pcentro, double raio, BaseMaterial material, Vec3 intensidade, double graus);
    int printObj(bool printMenu = false) override;
    void handleChange(int option) override;
};