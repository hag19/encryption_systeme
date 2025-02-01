#ifndef DEF_HEADER_ESGI_SPACE_CRAFT_PROJECTILE
#define DEF_HEADER_ESGI_SPACE_CRAFT_PROJECTILE

#include "Position.h"
#include <SDL/SDL.h>

struct Game;
struct Ship;

typedef struct Projectile Projectile;
struct Projectile {
	Position position;
	int projectileId;
	int used;
	int (*action)(Projectile *, struct Ship *, struct Game *);
	void (*draw)(Projectile *, SDL_Surface *, int, int, int, int);
};

Projectile * Projectile_alloc(Position position);

#endif