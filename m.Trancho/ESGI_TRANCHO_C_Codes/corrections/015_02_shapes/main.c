/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 15.
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
const char * titre = "ESGI shapes draw";

int call_command(char shape_id);
/* Valeurs attendues entre -1 et 1 pour les coordonnées et 0 et 1 pour les couleurs : */
void draw_circle(double center_x, double center_y, double rayon, double r, double g, double b);
void draw_line(double start_x, double start_y, double end_x, double end_y, double r, double g, double b);

void read_circle() {
  double cx, cy, rayon;
  double r, g, b;
  scanf("%lf %lf %lf %lf %lf %lf", &cx, &cy, &rayon, &r, &g, &b);
  draw_circle(cx, cy, rayon, r, g, b); 
}

void read_line() {
  double sx, sy, ex, ey;
  double r, g, b;
  scanf("%lf %lf %lf %lf %lf %lf %lf", &sx, &sy, &ex, &ey, &r, &g, &b);
  draw_line(sx, sy, ex, ey, r, g, b);
}

int read_command() {
  char command;
  printf("Entrez une commande :\n - c : cercle (centre(x, y) rayon couleur(r, g, b))\n - l : ligne (debut(x, y) fin(x, y) couleur(r, g, b))\n - q : quitter\n>>> ");
  scanf(" %c", &command);
  return call_command(command);
}

int call_command(char shape_id) {
  switch(shape_id) {
    case 'c' : read_circle(); break;
    case 'l' : read_line(); break;
    case 'q' : return 0;
    default : break;
  }
  return 1;
}

SDL_Surface * ecran = NULL;

void draw_circle(double center_x, double center_y, double rayon, double r, double g, double b) {
  filledCircleRGBA(ecran, center_x * largeur / 2. + largeur / 2., -center_y * hauteur / 2. + hauteur / 2., 
    rayon * fmin(largeur, hauteur) / 2., r * 255, g * 255, b * 255, 255);
}

void draw_line(double start_x, double start_y, double end_x, double end_y, double r, double g, double b) {
  lineRGBA(ecran, start_x * largeur / 2. + largeur / 2., -start_y * hauteur / 2. + hauteur / 2., 
    end_x * largeur / 2. + largeur / 2., -end_y * hauteur / 2. + hauteur / 2., r * 255, g * 255, b * 255, 255);
}

int main(int argc, char * argv[]) {
  srand(time(NULL));
  /* Création d'une fenêtre SDL : */
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption(titre, NULL);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
  SDL_Flip(ecran);
  
  while(read_command()) {
    
    SDL_Flip(ecran);
    SDL_Delay(1000 / 60);
  }
  
  SDL_FreeSurface(ecran);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}