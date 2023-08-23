#include <SDL2/SDL.h>
#include "../Ray.h"

class Objeto {

public:

    int id;
    SDL_Color cor;

    Objeto(int id, SDL_Color cor);
    ~Objeto();

    virtual bool intersecta(Ray raycaster) = 0;
};

