/*  gcc 03_random_tests_start.c -DSDL_MAIN_HANLDED -lmingw32 -lSDLmain -lSDL -lSDL_gfx -o prog; ./prog.exe */

#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <windows.h>

#define MAX_ENTRIES 20

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 600;
const char * titre = "ESGI random";
SDL_Surface * ecran = NULL;

const int trials = 10000000;
int essai = 0;
unsigned long counts[MAX_ENTRIES];

void draw_random() {
	
	char buffer[1024];
	int i;
	unsigned long max_count = 0;
	unsigned long sum_count = 0;
	for(i = 0; i < MAX_ENTRIES; ++i) {
		max_count = (max_count > counts[i]) ? max_count : counts[i];
		sum_count += counts[i];
	}
	for(i = 0; i < MAX_ENTRIES; ++i) {
		boxRGBA(ecran, 
			300, 100 + (i * (hauteur - 200)) / (MAX_ENTRIES + 1), 
			300 + ((largeur - 400) * (counts[i])) / max_count, 100 + ((i + 1) * (hauteur - 200)) / (MAX_ENTRIES + 1), 
			127, 127, 127, 255);
		rectangleRGBA(ecran, 
			300, 100 + (i * (hauteur - 200)) / (MAX_ENTRIES + 1), 
			300 + ((largeur - 400) * (counts[i])) / max_count, 100 + ((i + 1) * (hauteur - 200)) / (MAX_ENTRIES + 1), 
			255, 255, 255, 255);
		sprintf(buffer, "P(X = %d) = %g", i, (double)counts[i] / sum_count);
		stringRGBA(ecran, 10, 100 + ((i + 0.5) * (hauteur - 200)) / (MAX_ENTRIES + 1), buffer, 255, 255, 255, 255);
	}
	sprintf(buffer, "%d / %d essais", essai, trials);
	stringRGBA(ecran, 10, 10, buffer, 255, 255, 255, 255);
}

int uniform_random(int entries) {
	return rand() % entries;
}

int baised_fair_take_random(int entries) {
	int i;
	for(i = 0; i < entries; ++i) {
		if(rand() % entries == 0) return i;
	}
	return entries - 1;
}

/* TODO : vos fonctions */

void test_random(int entries, int (*random)(int)) {
	char buffer[1024];
	int i;
	for(i = 0; i < MAX_ENTRIES; ++i) {
		counts[i] = 0;
	}
	unsigned long t = 1;
	int updates = 0;
	for(essai = 0; essai < trials; ++essai) {
		++(counts[random(entries)]);
		if(essai > t || essai % 10000 == 0) {
			SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
		  	draw_random();
			SDL_Flip(ecran);
			if(essai > t) {
				t *= 2;
				/*SDL_Delay(1 + 1000 / (++updates));*/
			}
		}
	}
}

int read_command() {
	printf("Aléatoires :\n");
	printf(" 1. uniform random\n");
	printf(" 2. baised fair take random\n");
	/* TODO : lister vos fonctions */
	printf(" 0. quitter\n");
	printf(">>> ");
	int choix;
	scanf("%d", &choix);
	if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
      fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
      SDL_Quit();
      exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption(titre, NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
    SDL_Flip(ecran);
	switch(choix) {
		case 0 : return 0;
		case 1 : test_random(MAX_ENTRIES, uniform_random); break;
		case 2 : test_random(MAX_ENTRIES, baised_fair_take_random); break;
		/* TODO : lister l'appel de vos fonctions */
		default : break;
	}
	SDL_FreeSurface(ecran);
	ecran = NULL;
	return 1;
}

int main(int argc, char * argv[]) {
  AllocConsole();
  freopen("CON", "w", stdout);
  freopen("CON", "w", stderr);
  freopen("CON", "r", stdin);
  srand(time(NULL));
  /* Création d'une fenêtre SDL : */
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  
  while(read_command());
  
  SDL_Quit();
  exit(EXIT_SUCCESS);
}