/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include "../include/Game.h"

#include <stdlib.h>
#include <math.h>
#include <SDL/SDL_gfxPrimitives.h>

Game Game_create(int width, int height, Ship * player) {
  Game game;
  game.width = width;
  game.height = height;
  game.player = player;
  game.opponents = List_empty();
  return game;
}

void Game_free(Game * game) {
  if(game == NULL) {
    return;
  }
  Ship_free(game->player);
  game->player = NULL;
  List_free(&(game->opponents));
}

void Game_draw(Game * game, SDL_Surface * ecran) {
  Ship_draw(game->player, ecran);
  
  void process(Ship * ship) {
    Ship_draw(ship, ecran);
  };
  List_foreach(game->opponents, (void (*)(void *))process);
}

void Game_play_step(Game * game) {
  Ship_actions(game->player, game);
  
  void processIA(Ship * ship) {
    Controler_ia(&(ship->control), ship, game);
    void subprocess(Ship * subship) {
      if(subship->shipId == ship->shipId) {
        return;
      }
      double distance = Position_distance(subship->position, ship->position);
      if(distance > 2. * ship->width + fabs(ship->moving.x)) {
        return;
      }
      if(ship->position.x < subship->position.x) {
        ship->control.move_right = 0;
      } else if(ship->position.x > subship->position.x) {
        ship->control.move_left = 0;
      }
    };
    List_foreach(game->opponents, (void (*)(void *))subprocess);
  };
  List_foreach(game->opponents, (void (*)(void *))processIA);
  
  void process(Ship * ship) {
    Ship_actions(ship, game);
  };
  List_foreach(game->opponents, (void (*)(void *))process);
}