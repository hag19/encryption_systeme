/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 37.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 800;
const char * titre = "ESGI jump";

/* Coordonnées du joueur (position) : */
float px, py;
/* Vitesse du joueur (déplacement) : */
float vx, vy;
/* Accélération du joueur (saut, eau) : */
float ax, ay;

/* Coordonnées de l'objectif : */
float ox, oy;
/* Coordonnées de l'adversaire : */
float ex, ey;

/* Position de la caméra et échelle de la vue : */
float cx, cy, cz;

float distance(float first_x, float first_y, float second_x, float second_y) {
  return sqrt((first_x - second_x) * (first_x - second_x) + (first_y - second_y) * (first_y - second_y));
}

float hauteur_terrain(float x) {
  return 0.5 * (200 * sin(x / 400.) + 100 * sin(x / 117.) + 25 * sin(x / 51.) + 10 * sin(x / 12.) + 10 * sin((x + 10) / 13.));
}

void placer_objectif() {
  int distance = (rand() % 1000) + 200;
  if(rand() % 2 == 0) {
    distance *= -1;
  }
  ox = px + distance;
  oy = hauteur_terrain(ox) - 200;
}

void placer_adversaire() {
  int distance = 5000;
  if(rand() % 2 == 0) {
    distance *= -1;
  }
  ex = px + distance;
  ey = hauteur_terrain(ex);
}

int ecran_depuis_camera_x(float x) {
  return ((x - cx) * largeur / 2) / cz + largeur / 2;
}

int ecran_depuis_camera_y(float y) {
  return ((y - cy) * hauteur / 2) / cz + hauteur / 2;
}

float camera_depuis_ecran_x(int x) {
  return 2. * ((x - largeur / 2) * cz) / largeur + cx;
}

float camera_depuis_ecran_y(int y) {
  return 2. * ((y - hauteur / 2) * cz) / hauteur + cy;
}

float ecran_depuis_camera_z(int z) {
  return (z * largeur / 2.) / cz;
}

float camera_depuis_ecran_z(int z) {
  return (2 * z * cz) / largeur;
}

void affichage(SDL_Surface * ecran) {
  /* Remplissage de l'écran par un gris foncé uniforme : */
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
  /* Affichage du joueur : */
  filledCircleRGBA(ecran, ecran_depuis_camera_x(px), ecran_depuis_camera_y(py), ecran_depuis_camera_z(25), 51, 204, 51, 255);
  
  filledCircleRGBA(ecran, ecran_depuis_camera_x(ox), ecran_depuis_camera_y(oy), ecran_depuis_camera_z(25), 204, 204, 51, 255);
  
  filledCircleRGBA(ecran, ecran_depuis_camera_x(ex), ecran_depuis_camera_y(ey), ecran_depuis_camera_z(50), 204, 51, 51, 255);
  
  int x, y, z;
  for(x = 0; x < largeur; ++x) {
    y = ecran_depuis_camera_y(hauteur_terrain(camera_depuis_ecran_x(x)));
    z = ecran_depuis_camera_y(0);
    boxRGBA(ecran, x, y, x + 1, z, 51, 51, 204, 127);
    boxRGBA(ecran, x, y, x + 1, hauteur, 102, 51, 51, 255);
    boxRGBA(ecran, x, y, x + 1, y + ecran_depuis_camera_z(5), 51, 102, 51, 255);
  }
}

int calculs(int score) {
  ay += (py > 0) ? -1 : 10;
  vx += ax;
  vy += ay;
  px += vx;
  py += vy;
  ax = 0;
  ay = 0;
  int ht = hauteur_terrain(px);
  if(py > ht) {
    py = ht;
    vy = 0;
  }
  
  if(distance(px, py, ox, oy) < 50) {
    score += 1;
    placer_objectif();
  }
  
  if(distance(px, py, ex, ey) < 50) {
    score -= 10;
    if(score < 0) {
      score = 0;
    }
    placer_adversaire();
  }
  
  int av = (ey > 0) ? 2 : 5;
  if(px < ex) {
    ex -= av;
  } else {
    ex += av;
  }
  ey = hauteur_terrain(ex);
  
  return score;
}

void action_jump() {
  ay -= (py > 0) ? 40 : 80;
}

void action_droite() {
  int move = (py > 0) ? 8 : 20;
  vx = move;
}

void action_gauche() {
  int move = (py > 0) ? 8 : 20;
  vx = -move;
}

void action_sans_direction() {
  vx = 0;
}

void deplacer_camera() {
  float d = distance(cx, cy, px, py);
  if(d > cz / 2.) {
    cx -= 0.125 * d * (cx - px) / (2. * cz);
    cy -= 0.125 * d * (cy - py) / (2. * cz);
  }
}

int main() {
  srand(time(NULL));
  /* Création d'une fenêtre SDL : */
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Еrror in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Surface * ecran = NULL;
  if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    fprintf(stderr, "Еrror in SDL_SetVideoMode : %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption(titre, NULL);
  
  /* Placement du joueur au centre de la fenêtre : */
  px = 0;
  py = 0;
  vx = 0;
  vy = 0;
  ax = 0;
  ay = 0;
  
  cx = 0;
  cy = 0;
  cz = 500;
  
  int active = 1;
  SDL_Event event;
  int moving_right = 0;
  int moving_left = 0;
  int jump = 0;
  
  int score = 0;
  unsigned int temps;
  char display[100];
  
  placer_objectif();
                                   
  while(active) {
    
    temps = SDL_GetTicks();
    affichage(ecran);
    sprintf(display, "Score : %d", score);
    stringRGBA(ecran, 5, 5, display, 255, 255, 255, 255);
    sprintf(display, "Temps : %u:%02u:%02u s", (temps / 1000) / 60, (temps / 1000) % 60, (temps % 1000) / 10);
    stringRGBA(ecran, 5, 25, display, 255, 255, 255, 255);
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
            
            case SDLK_z :
            case SDLK_UP : {
              if(! jump) {
                action_jump();
              }
              jump = 1;
            } break;
            
            case SDLK_d :
            case SDLK_RIGHT : {
              moving_right = 1;
            } break;
            
            case SDLK_q :
            case SDLK_LEFT : {
              moving_left = 1;
            } break;
          }
        } break;
        
        case SDL_KEYUP : {
          switch(event.key.keysym.sym) {
            case SDLK_z :
            case SDLK_UP : {
              jump = 0;
            } break;
            
            case SDLK_d :
            case SDLK_RIGHT : {
              moving_right = 0;
            } break;
            
            case SDLK_q :
            case SDLK_LEFT : {
              moving_left = 0;
            } break;
          }
        } break;
        
        case SDL_MOUSEBUTTONDOWN : {
          switch(event.button.button) {
            case SDL_BUTTON_WHEELUP : {
              cz *= 0.8;
              if(cz < 1) {
                cz = 1;
              }
            } break;
            
            case SDL_BUTTON_WHEELDOWN : {
              cz /= 0.8;
              if(cz > 10000) {
                cz = 10000;
              }
            } break;
          }
        } break;
      }
    }
    
    if(moving_right && moving_left) {
      action_sans_direction();
    } else if(moving_right) {
      action_droite();
    } else if(moving_left) {
      action_gauche();
    } else {
      action_sans_direction();
    }
    score = calculs(score);
    
    deplacer_camera();
    
    if(score >= 10) {
      affichage(ecran);
      sprintf(display, "Score : %d", score);
      stringRGBA(ecran, 5, 5, display, 255, 255, 255, 255);
      sprintf(display, "Temps : %u:%02u:%02u s", (temps / 1000) / 60, (temps / 1000) % 60, (temps % 1000) / 10);
      stringRGBA(ecran, 5, 25, display, 255, 255, 255, 255);
      stringRGBA(ecran, largeur / 2 - 10, hauteur / 2, "BRAVO !", 255, 255, 255, 255);
      SDL_Flip(ecran);
      SDL_Delay(3000);
      active = 0;
    }
    
    SDL_Delay(1000 / 60);
  }
                                  
  SDL_FreeSurface(ecran);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}