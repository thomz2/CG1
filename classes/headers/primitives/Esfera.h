#include "./math/Vec3.h"
#include "./Objeto.h"
#include "../Ray.h"

class Esfera : public Objeto {
    public:
    Vec3 PCentro;
    double raio;

    Esfera(int id, SDL_Color cor, Vec3 Pcentro, double raio);
    
    bool intersecta(Ray raycaster) override;

    // Pin = olho observador
    Vec3 getW(Vec3 Pin); 
};