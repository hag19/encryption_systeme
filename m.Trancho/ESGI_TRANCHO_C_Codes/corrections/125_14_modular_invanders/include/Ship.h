/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

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
  void * userData;
  void * dlptr;
};

Controler Controler_create();

void Controler_draw(SDL_Surface * ecran, Controler * control, Ship * ship);

void Controler_move(Controler * control, Ship * ship, struct Game * game);

void Controler_ia(Controler * control, Ship * ship, struct Game * game);

Ship * Ship_alloc(int team, Position position);

void Ship_free(Ship * ship);

Ship * Ship_load(const char * path, int team, Position position);

void Ship_compute(Ship * ship);

void Ship_draw(Ship * ship, SDL_Surface * ecran);

void Ship_action(Ship * ship, struct Game * game);

void Ship_actions(Ship * ship, struct Game * game);

int Ship_attack(Projectile * projectile, double range, Ship * ship);

void Ship_apply_damages(double damages, Ship * ship);

#endif