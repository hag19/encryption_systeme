#ifndef DEF_HEADER_ESGI_SPACE_CRAFT_SHIP
#define DEF_HEADER_ESGI_SPACE_CRAFT_SHIP

#include "Stats.h"
#include "Position.h"
#include "List.h"
#include "Component.h"

#define SHIP_SCALE 8

typedef struct Controler Controler;
struct Controler {
	int move_forward;
	int move_backward;
	int move_left;
	int move_right;
	int ship_action;
	int reload_action;
};

struct Game;

typedef struct Ship Ship;
struct Ship {
	Stats stats;
	int width;
	int height;
	int team;
	double health;
	int shipId;
	Position position;
	Position moving;
	List components;
	List projectiles;
	Controler control;
};

Controler Controler_create();

Ship * Ship_alloc(int team, Position position);

Ship * Ship_load(const char * path, int team, Position position);

int Ship_attack(Projectile * projectile, double range, Ship * ship);

void Ship_apply_damages(double damages, Ship * ship);

#endif