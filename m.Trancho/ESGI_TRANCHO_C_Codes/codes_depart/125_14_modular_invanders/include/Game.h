#ifndef DEF_HEADER_ESGI_SPACE_CRAFT_GAME
#define DEF_HEADER_ESGI_SPACE_CRAFT_GAME

#include "Ship.h"
#include "Projectile.h"
#include <SDL/SDL.h>

typedef struct Game Game;
struct Game {
	int width;
	int height;
	Ship * player;
	List opponents;
};

Game Game_create(int width, int height, Ship * player);

void Game_free(Game * game);

void Game_draw(Game * game, SDL_Surface * ecran);

void Game_play_step(Game * game);

#endif