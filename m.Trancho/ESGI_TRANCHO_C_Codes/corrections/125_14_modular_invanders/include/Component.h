/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#ifndef DEF_HEADER_ESGI_SPACE_CRAFT_COMPONENT
#define DEF_HEADER_ESGI_SPACE_CRAFT_COMPONENT

#include "Stats.h"
#include "Position.h"
#include "Projectile.h"
#include <SDL/SDL.h>

struct Ship;
struct Game;

typedef enum {
  CT_NONE = 0,
  CT_COCKPIT,
  CT_ARMOR,
  CT_WEAPON,
  CT_PULSOR,
  CT_UTILITY
} ComponentType;

typedef struct Component Component;
struct Component {
  ComponentType type;
  Stats stats;
  int width;
  int height;
  int componentId;
  Position position;
  void (*action)(Component *, struct Ship *, struct Game *);
  void (*draw)(Component *, SDL_Surface *, int, int, int, int);
  void * userData;
  void * dlptr;
};

Component * Component_alloc(ComponentType type, Stats stats, 
  int width, int height, Position position);

void Component_free(Component * component);

Component * Component_load(const char * path, Position position);

#endif