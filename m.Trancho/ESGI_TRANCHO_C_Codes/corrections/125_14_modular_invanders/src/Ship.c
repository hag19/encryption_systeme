/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include "../include/Ship.h"

#include <stdlib.h>
#include <assert.h>
#include <dlfcn.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "../include/Game.h"

static int LastShipId = 0;

Controler Controler_create() {
  Controler control;
  control.move_forward = 0;
  control.move_backward = 0;
  control.move_left = 0;
  control.move_right = 0;
  control.ship_action = 0;
  control.reload_action = 0;
  return control;
}

void Controler_draw(SDL_Surface * ecran, Controler * control, Ship * ship) {
  double coeff;
  if(control->move_forward) {
    coeff = 1. + -0.1 * ship->moving.y;
    if(coeff < 0.1) coeff = 0.1;
    lineRGBA(ecran, 
      ship->position.x - ship->width, 
      ship->position.y - ship->height, 
      ship->position.x + ship->width, 
      ship->position.y - ship->height, 
      255, 255, 0, 255);
    lineRGBA(ecran, 
      ship->position.x - ship->width / ((coeff < 1.) ? 1. : coeff), 
      ship->position.y - coeff * ship->height, 
      ship->position.x + ship->width / ((coeff < 1.) ? 1. : coeff), 
      ship->position.y - coeff * ship->height, 
      0, 255, 0, 255);
  }
  if(control->move_backward) {
    coeff = 1. + 0.1 * ship->moving.y;
    if(coeff < 0.1) coeff = 0.1;
    lineRGBA(ecran, 
      ship->position.x - ship->width, 
      ship->position.y + ship->height, 
      ship->position.x + ship->width, 
      ship->position.y + ship->height, 
      255, 255, 0, 255);
    lineRGBA(ecran, 
      ship->position.x - ship->width / ((coeff < 1.) ? 1. : coeff), 
      ship->position.y + coeff * ship->height, 
      ship->position.x + ship->width / ((coeff < 1.) ? 1. : coeff), 
      ship->position.y + coeff * ship->height, 
      0, 255, 0, 255);
  }
  if(control->move_left) {
    coeff = 1. + -0.1 * ship->moving.x;
    if(coeff < 0.1) coeff = 0.1;
    lineRGBA(ecran, 
      ship->position.x - ship->width, 
      ship->position.y - ship->height, 
      ship->position.x - ship->width, 
      ship->position.y + ship->height, 
      255, 255, 0, 255);
    lineRGBA(ecran, 
      ship->position.x - coeff * ship->width, 
      ship->position.y - ship->height / ((coeff < 1.) ? 1. : coeff), 
      ship->position.x - coeff * ship->width, 
      ship->position.y + ship->height / ((coeff < 1.) ? 1. : coeff), 
      0, 255, 0, 255);
  }
  if(control->move_right) {
    coeff = 1. + 0.1 * ship->moving.x;
    if(coeff < 0.1) coeff = 0.1;
    lineRGBA(ecran, 
      ship->position.x + ship->width, 
      ship->position.y - ship->height, 
      ship->position.x + ship->width, 
      ship->position.y + ship->height, 
      255, 255, 0, 255);
    lineRGBA(ecran, 
      ship->position.x + coeff * ship->width, 
      ship->position.y - ship->height / ((coeff < 1.) ? 1. : coeff), 
      ship->position.x + coeff * ship->width, 
      ship->position.y + ship->height / ((coeff < 1.) ? 1. : coeff), 
      0, 255, 0, 255);
  }
}

void Controler_move(Controler * control, Ship * ship, Game * game) {
  double tmp;
  double bonus = (control->reload_action < 50) ? 1. : 0.0625;
  if(ship->team > 1) {
    tmp = ship->stats.forward_force;
    ship->stats.forward_force = ship->stats.backward_force;
    ship->stats.backward_force = tmp;
    tmp = ship->stats.left_force;
    ship->stats.left_force = ship->stats.right_force;
    ship->stats.right_force = tmp;
  }
  double coeff = 1.;
  if(control->move_forward && !(control->move_backward)) {
    coeff = bonus * ((ship->moving.y < 0) ? 1. : 3.);
    ship->moving.y -= coeff * ship->stats.forward_force / ship->stats.mass;
  } else if(control->move_backward && !(control->move_forward)) {
    coeff = bonus * ((ship->moving.y > 0) ? 1. : 3.);
    ship->moving.y += coeff * ship->stats.backward_force / ship->stats.mass;
  } else if(fabs(ship->moving.y) > 0) {
    double force = 2. * coeff * ((ship->moving.y < 0) ? (ship->stats.backward_force / ship->stats.mass) : -(ship->stats.forward_force / ship->stats.mass));
    if(fabs(ship->moving.y) > fabs(force)) {
      ship->moving.y += force;
    } else {
      ship->moving.y = 0;
    }
  }
  
  if(control->move_left && ! (control->move_right)) {
    coeff = bonus * ((ship->moving.x < 0) ? 1. : 3.);
    ship->moving.x -= coeff * ship->stats.left_force / ship->stats.mass;
  } else if(control->move_right && ! (control->move_left)) {
    coeff = bonus * ((ship->moving.x > 0) ? 1. : 3.);
    ship->moving.x += coeff * ship->stats.right_force / ship->stats.mass;
  } else if(fabs(ship->moving.x) > 0) {
    double force = 2. * coeff * ((ship->moving.x < 0) ? (ship->stats.right_force / ship->stats.mass) : -(ship->stats.left_force / ship->stats.mass));
    if(fabs(ship->moving.x) > fabs(force)) {
      ship->moving.x += force;
    } else {
      ship->moving.x = 0;
    }
  }
  
  if(ship->position.x < 0) {
    ship->moving.x = 0;
    ship->moving.x += 5000. / ship->stats.mass;
  } else if(ship->position.x > game->width) {
    ship->moving.x = 0;
    ship->moving.x += -5000. / ship->stats.mass;
  }
  
  if(ship->position.y < 0) {
    ship->moving.y = 0;
    ship->moving.y += 5000. / ship->stats.mass;
  } else if(ship->position.y > game->height) {
    ship->moving.y = 0;
    ship->moving.y += -5000. / ship->stats.mass;
  }
  
  ship->position.x += ship->moving.x;
  ship->position.y += ship->moving.y;
  
  if(control->ship_action && control->reload_action <= 0) {
    Ship_action(ship, game);
    control->ship_action = 1;
    control->reload_action = 20;
  }
  --(control->reload_action);
  if(ship->team > 1) {
    tmp = ship->stats.forward_force;
    ship->stats.forward_force = ship->stats.backward_force;
    ship->stats.backward_force = tmp;
    tmp = ship->stats.left_force;
    ship->stats.left_force = ship->stats.right_force;
    ship->stats.right_force = tmp;
  }
}

void Controler_ia(Controler * control, Ship * ship, Game * game) {
  if(game->player->position.x < ship->position.x) {
    control->move_left = 1;
  } else  {
    control->move_left = 0;
  }
  if(game->player->position.x > ship->position.x) {
    control->move_right = 1;
  } else  {
    control->move_right = 0;
  }
  if(fabs(game->player->position.x - ship->position.x) < 300.) {
    control->ship_action = 1;
  } else {
    control->ship_action = 0;
  }
}

Ship * Ship_alloc(int team, Position position) {
  Ship * ship = NULL;
  assert(ship = (Ship *)malloc(sizeof(Ship)));
  ship->stats = Stats_zero();
  ship->width = 0;
  ship->height = 0;
  ship->team = team;
  ship->health = 0.;
  ship->shipId = ++LastShipId;
  ship->position = position;
  ship->moving = Position_create(0., 0.);
  ship->components = List_empty();
  ship->projectiles = List_empty();
  ship->control = Controler_create();
  ship->userData = NULL;
  ship->dlptr = NULL;
  return ship;
}

void Ship_free(Ship * ship) {
  if(ship == NULL) {
    return;
  }
  if(ship->dlptr) {
    dlclose(ship->dlptr);
  }
  List_free(&(ship->projectiles));
  List_free(&(ship->components));
  free(ship->userData);
  free(ship);
}

Ship * Ship_load(const char * path, int team, Position position) {
  void * dlptr = NULL;
  if((dlptr = dlopen(path, RTLD_NOW)) == NULL) {
    fprintf(stderr, "Erreur d'ouverture du vaisseau \"%s\"\n%s\n", path, dlerror());
    exit(EXIT_FAILURE);
  }
  Ship * (*instantiate)(int, Position) = NULL;
  if((instantiate = (Ship * (*)(int, Position))dlsym(dlptr, "Ship_instantiate")) == NULL) {
    fprintf(stderr, "Erreur de chargement du vaisseau \"%s\"\n%s\n", path, dlerror());
    exit(EXIT_FAILURE);
  }
  Ship * ship = (*instantiate)(team, position);
  ship->dlptr = dlptr;
  Ship_compute(ship);
  Stats_display(stdout, &(ship->stats));
  return ship;
}

void Ship_compute(Ship * ship) {
  ship->stats = Stats_zero();
  ship->width = 0;
  ship->height = 0;
  void process(Component * component) {
    Stats_add(&(ship->stats), &(component->stats));
    int offset = ((ship->team > 1) ? -1 : 1);
    if(offset * component->position.x + component->width > ship->width / SHIP_SCALE) {
      ship->width = offset * component->position.x * SHIP_SCALE + component->width * SHIP_SCALE;
    } else if(offset * component->position.x - component->width < -(ship->width) / SHIP_SCALE) {
      ship->width = -(offset * component->position.x) * SHIP_SCALE + component->width * SHIP_SCALE;
    }
    if(offset * component->position.y + component->height > ship->height / SHIP_SCALE) {
      ship->height = offset * component->position.y * SHIP_SCALE + component->height * SHIP_SCALE;
    } else if(offset * component->position.y - component->height < -(ship->height) / SHIP_SCALE) {
      ship->height = -(offset * component->position.y) * SHIP_SCALE + component->height * SHIP_SCALE;
    }
  };
  List_foreach(ship->components, (void (*)(void *))process);
  ship->health = ship->stats.health;
}

void Ship_draw(Ship * ship, SDL_Surface * ecran) {
  int offset = ((ship->team > 1) ? -1 : 1);
  /*rectangleRGBA(ecran, ship->position.x - ship->width, ship->position.y - ship->height, ship->position.x + ship->width, ship->position.y + ship->height, 255, 0, 0, 255);*/
  void process(Component * component) {
    component->draw(component, ecran, ship->position.x + offset * SHIP_SCALE * component->position.x, ship->position.y + offset * SHIP_SCALE * component->position.y, SHIP_SCALE, ship->team);
  };
  List_foreach(ship->components, (void (*)(void *))process);
  void processProjectiles(Projectile * projectile) {
    projectile->draw(projectile, ecran, projectile->position.x, projectile->position.y, SHIP_SCALE, ship->team);
  };
  List_foreach(ship->projectiles, (void (*)(void *))processProjectiles);
  Controler_draw(ecran, &(ship->control), ship);
  boxRGBA(ecran, ship->position.x - ship->width - 1, ship->position.y - ship->height - 1, ship->position.x + ship->width + 1, ship->position.y - ship->height - SHIP_SCALE + 1, 0, 0, 0, 255);
  if(ship->health > 0.) {
    boxRGBA(ecran, ship->position.x - ship->width, ship->position.y - ship->height, ship->position.x + (ship->health / ship->stats.health) * 2 * ship->width - ship->width, ship->position.y - ship->height - SHIP_SCALE, 204, 204, 204, 255);
  }
}

void Ship_action(Ship * ship, Game * game) {
  if(ship->health < 0.) {
    return;
  }
  void process(Component * component) {
    if(component->action)
      component->action(component, ship, game);
  };
  List_foreach(ship->components, (void (*)(void *))process);
}

void Ship_actions(Ship * ship, Game * game) {
  List * current = &(ship->projectiles);
  Projectile * projectile;
  while(*current != NULL) {
    projectile = (Projectile *)((*current)->value);
    if(! (projectile->action(projectile, ship, game))) {
      Projectile_free(projectile);
      List node = *current;
      *current = (*current)->next;
      free(node);
    } else {
      current = &((*current)->next);
    }
  }
  ship->health += 0.01 * ship->stats.repair;
  if(ship->health > ship->stats.health) {
    ship->health = ship->stats.health;
  }
  if(ship->health < 0.) {
    ship->health = 0.;
    ship->control.reload_action = 100;
    return;
  }
  Controler_move(&(ship->control), ship, game);
}

int Ship_attack(Projectile * projectile, double range, Ship * ship) {
  int collision = 0;
  range *= SHIP_SCALE;
  void processProjectiles(Projectile * current) {
    if(! collision 
    && Position_distance(projectile->position, current->position) < 2 * range) {
      projectile->used = 1;
      current->used = 1;
      collision = 1;
    }
  };
  List_foreach(ship->projectiles, (void (*)(void *))processProjectiles);
  if(collision) {
    return 0;
  }
  collision = (projectile->position.x + range > ship->position.x - ship->width)
  && (projectile->position.y + range > ship->position.y - ship->height)
  && (projectile->position.x - range < ship->position.x + ship->width)
  && (projectile->position.y - range < ship->position.y + ship->height);
  if(! collision) {
    return 0;
  }
  projectile->used = 1;
  return 1;
}

void Ship_apply_damages(double damages, Ship * ship) {
  ship->health -= 200. * damages / ship->stats.armor;
}