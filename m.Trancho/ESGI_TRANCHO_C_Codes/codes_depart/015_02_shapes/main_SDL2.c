#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 800;
const char * titre = "ESGI shapes draw";

int call_command(char shape_id);
/* Valeurs attendues entre -1 et 1 pour les coordonnées et 0 et 1 pour les couleurs : */
void draw_circle(double center_x, double center_y, double rayon, double r, double g, double b);
void draw_line(double start_x, double start_y, double end_x, double end_y, double r, double g, double b);

void read_circle() {
	/* TODO lire centre et rayon d'un cercle */
	/* TODO lire couleur RGB */
}

void read_line() {
	/* TODO lire debut et fin d'une ligne */
	/* TODO lire couleur RGB */
}

int read_command() {
	/* TODO lire les commandes du joueur */
	return call_command('q');
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

SDL_Renderer * ecran = NULL;

void draw_circle(double center_x, double center_y, double rayon, double r, double g, double b) {
	filledCircleRGBA(ecran, center_x * largeur / 2. + largeur / 2., -center_y * hauteur / 2. + hauteur / 2., 
		rayon * fmin(largeur, hauteur) / 2., r * 255, g * 255, b * 255, 255);
}

void draw_line(double start_x, double start_y, double end_x, double end_y, double r, double g, double b) {
	lineRGBA(ecran, start_x * largeur / 2. + largeur / 2., -start_y * hauteur / 2. + hauteur / 2., 
		end_x * largeur / 2. + largeur / 2., -end_y * hauteur / 2. + hauteur / 2., r * 255, g * 255, b * 255, 255);
}

int main(int argc, char * argv[]) {
  SDL_Window * window = NULL;
  srand(time(NULL));
  /* Création d'une fenêtre SDL : */
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  if(SDL_CreateWindowAndRenderer(largeur, hauteur, SDL_WINDOW_SHOWN, &window, &ecran) != 0) {
    fprintf(stderr, "Error in SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_SetWindowTitle(window, titre);
  SDL_SetRenderDrawColor(ecran, 51, 51, 51, 255);
  SDL_RenderClear(ecran);
  SDL_RenderPresent(ecran);
  
  while(read_command()) {
    
    SDL_RenderPresent(ecran);
    SDL_Delay(1000 / 60);
  }
  
  SDL_DestroyRenderer(ecran);
  SDL_DestroyWindow(window);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}
