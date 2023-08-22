#include "../headers/Vec3.h"
#include "../headers/Ray.h"

class Esfera {
    public:
    Vec3 PCentro;
    double raio;

    Esfera(Vec3 Pcentro, double raio);
    
    bool intersecta(Ray raycaster);

    private:
    // Pin = olho observador
    Vec3 getW(Vec3 Pin); 
};