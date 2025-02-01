/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <Game.h>
#include <Component.h>

/* Paramètres de la fenêtre : */
const int largeur = 1200;
const int hauteur = 900;
const char * titre = "ESGI SpaceCraft";
Game game;

void affichage(SDL_Surface * ecran) {
  unsigned long t = SDL_GetTicks();
  int x, y, i;
  /* Remplissage de l'écran par un gris foncé uniforme : */
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 25, 25, 53));
  for(i = 1; i < 100; ++i) {
    x = 123 * i * i + 800 * sin((t + i * i * 100.) / 20000.);
    y = 753 * i + t / 4. + 100 * cos((t + i * 100.) / 2000.);
    x = ((x % largeur) + largeur) % largeur;
    y = ((y % hauteur) + hauteur) % hauteur;
    double coeff = 10. / (10. + i);
    boxRGBA(ecran, x - 81 * coeff, y - 81 * coeff, x + 81 * coeff, y + 81 * coeff, 204, 204, 204, 3);
    boxRGBA(ecran, x - 27 * coeff, y - 27 * coeff, x + 27 * coeff, y + 27 * coeff, 204, 204, 204, 9);
    boxRGBA(ecran, x - 9 * coeff, y - 9 * coeff, x + 9 * coeff, y + 9 * coeff, 204, 204, 204, 27);
    boxRGBA(ecran, x - 3 * coeff, y - 3 * coeff, x + 3 * coeff, y + 3 * coeff, 204, 204, 204, 81);
    boxRGBA(ecran, x - 1, y - 1, x + 1, y + 1, 204, 204, 204, 255);
  }
}

int main(int argc, char * argv[]) {
  Ship * ship = Ship_load((argc > 1) ? argv[1] : "extensions/Ship_basic.so", 1, Position_create(largeur / 2, 3 * hauteur / 4));
  game = Game_create(largeur, hauteur, ship);
  List_add(&(game.opponents), Ship_load((argc > 2) ? argv[2] : "extensions/Ship_basic.so", 2, Position_create(largeur / 2, hauteur / 8)));
  List_add(&(game.opponents), Ship_load((argc > 2) ? argv[2] : "extensions/Ship_basic.so", 2, Position_create(largeur / 4, hauteur / 9)));
  List_add(&(game.opponents), Ship_load((argc > 2) ? argv[2] : "extensions/Ship_basic.so", 2, Position_create(3 * largeur / 4, hauteur / 9)));
  List_add(&(game.opponents), Ship_load((argc > 2) ? argv[2] : "extensions/Ship_tank.so", 2, Position_create(largeur / 4, 2 * hauteur / 9)));
  List_add(&(game.opponents), Ship_load((argc > 2) ? argv[2] : "extensions/Ship_tank.so", 2, Position_create(3 * largeur / 4, 2 * hauteur / 9)));
  srand(time(NULL));
  /* Création d'une fenêtre SDL : */
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Surface * ecran = NULL;
  if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption(titre, NULL);
  
  int active = 1;
  SDL_Event event;
  
  while(active) {
    
    affichage(ecran);
    Game_draw(&game, ecran);
    SDL_Flip(ecran);
    
    while(SDL_PollEvent(&event)) {
      
      switch(event.type) {
        /* Utilisateur clique sur la croix de la fenêtre : */
        case SDL_QUIT : {
          active = 0;
        } break;
        
        /* Utilisateur enfonce une touche du clavier : */
        case SDL_KEYDOWN : {
          switch(event.key.keysym.sym) {
            /* Touche Echap : */
            case SDLK_ESCAPE : {
              active = 0;
            } break;
            
            case SDLK_SPACE : {
              game.player->control.ship_action = 1;
            } break;
            
            case SDLK_z :
            case SDLK_UP : {
              game.player->control.move_forward = 1;
            } break;
            
            case SDLK_s :
            case SDLK_DOWN : {
              game.player->control.move_backward = 1;
            } break;
            
            case SDLK_q :
            case SDLK_LEFT : {
              game.player->control.move_left = 1;
            } break;
            
            case SDLK_d :
            case SDLK_RIGHT : {
              game.player->control.move_right = 1;
            } break;
            
            default : break;
          }
        } break;
        
        case SDL_KEYUP : {
          switch(event.key.keysym.sym) {
            case SDLK_SPACE : {
              game.player->control.ship_action = 0;
            } break;
            
            case SDLK_z :
            case SDLK_UP : {
              game.player->control.move_forward = 0;
            } break;
            
            case SDLK_s :
            case SDLK_DOWN : {
              game.player->control.move_backward = 0;
            } break;
            
            case SDLK_q :
            case SDLK_LEFT : {
              game.player->control.move_left = 0;
            } break;
            
            case SDLK_d :
            case SDLK_RIGHT : {
              game.player->control.move_right = 0;
            } break;
            
            default : break;
          }
        } break;
        
        default : break;
      }
    }
    int delay = SDL_GetTicks() + 1000 / 60;
    Game_play_step(&game);
    delay -= SDL_GetTicks();
    if(delay > 0) {
      SDL_Delay(delay);
    }
  }
  
  SDL_FreeSurface(ecran);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}