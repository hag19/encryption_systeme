#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 600;
const char * titre = "ESGI delivery";

#define SELECT 10
#define GENERATE 1000

/* TODO : définir un modèle pour sauvegarder la liste utilisateur */

/* TODO : définir la liste utilisateur */

/* Nombre de points saisis par l'utilisateur : */
int taille = 0;

/* TODO : définir un modèle pour les solutions au problème */

/* Nombre de cycles d'optimisation des solutions : */
int generations = 0;
clock_t start;

void Entries_init() {
	/* TODO : initialise la liste de points à optimiser */
}

void Entries_update() {
	/* TODO : optimiser les solutions actuelles */
	++generations;
}

void addInput(int x, int y) {
	/* TODO : ajouter un point à la liste utilisateur */
	++taille;
}

void affichage(SDL_Surface * ecran) {
	/* Remplissage de l'écran par un gris foncé uniforme : */
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
	
	int i;
	double distance = 0.;
	/* TODO : dessiner la liste de points utilisateur et la solution la plus pertinente trouvée */
	/* TODO : calculer la distance totale de la proposition actuelle */
	char buffer[512];
	sprintf(buffer, "%d positions", taille);
	stringRGBA(ecran, 5, 5, buffer, 255, 255, 255, 255);
	if(generations == 0) {
		sprintf(buffer, "Distance totale : %g", distance);
	} else {
		sprintf(buffer, "Generation %d (%g s)", generations, (double)(clock() - start) / CLOCKS_PER_SEC);
	}
	stringRGBA(ecran, 5, 25, buffer, 255, 255, 255, 255);
	/* TODO : afficher distance des meilleures solutions */
}

int Points_save(const char * path, ...) {
	/* TODO : sauvegarder la liste de points de l'utilisateur */
	return 0;
}

int Points_load(const char * path, ...) {
	/* TODO : charger la liste de points de l'utilisateur */
	return 0;
}

int main(int argc, char * argv[]) {
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
	
	/* TODO : charger le fichier de points en argument si précisé : */
	
	int active = 1;
	int optimise = 0;
	SDL_Event event;
	
	while(active) {
		
		affichage(ecran);
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
					}
				} break;
				
				case SDL_KEYUP : {
					switch(event.key.keysym.sym) {
						case SDLK_SPACE : {
							if(! optimise) {
								Entries_init();
								start = clock();
							}
							optimise = 1;
						} break;
						
						case SDLK_s : {
							/* TODO : sauvegarder la liste de points actuelle */
						} break;
					}
				} break;
				
				case SDL_MOUSEBUTTONUP : {
					switch(event.button.button) {
						case SDL_BUTTON_LEFT : {
							if(! optimise) {
								addInput(event.button.x, event.button.y);
							}
						} break;
					}
				} break;
			}
		}
		if(optimise) {
			Entries_update();
			SDL_Delay(1);
		} else {
			SDL_Delay(1000 / 60);
		}
		
	}
	
	SDL_FreeSurface(ecran);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}