#include <SDL2/SDL.h>
#include "../headers/primitives/Objeto.h"
#include "../headers/Ray.h"

Objeto::Objeto(int id, SDL_Color cor) : id(id), cor(cor) {}

bool Objeto::intersecta(Ray raycaster) const {};