#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 800;
const char * titre = "ESGI labyrinthe";

/* Mon jeu va être génial, mais il y a encore quelques bugs. */
/* Merci de les corriger. Bob. */

/* TODO : allouer une grille (fonction grille_creer) */
/* TODO : coder in_grille */
/* Normalement, ça affiche un labyrinthe. */
/* TODO : corriger la caméra. */
/* TODO : tester pour :
/*  - grille_largeur = 1000 */
/*  - grille_hauteur = 1000 */
/* L'erreur vient d'appels récursifs qui explosent la pile. */
/* TODO : optimiser les appels récursifs de creuser . */
/* TODO : adapter le code pour des grilles 10000 x 10000 . */
/* TODO : optimiser l'affichage (vue proche et vue loin) . */
/* TODO : déplacer le joueur au clavier dans le labyrinthe . */
/* TODO : s'amuser à aller plus loin si vous le voulez ! */

/* Position de la caméra et échelle de la vue : */
float cx, cy, cz;

int player_x, player_y;
int exit_x, exit_y;

SDL_Surface * ecran = NULL;

char ** grille = NULL;
int grille_largeur = 100;
int grille_hauteur = 100;

/* TODO permettre déplacement caméra à la souris : */
double ecran_depuis_camera_x(double x) {
	return x / cz + cx;
}

double ecran_depuis_camera_y(double y) {
	return y / cz + cy;
}

double ecran_depuis_camera_z(double z) {
	return z / cz;
}

double camera_depuis_ecran_x(double x) {
	return x * cz - cx;
}

double camera_depuis_ecran_y(double y) {
	return y * cz - cy;
}

double camera_depuis_ecran_z(double z) {
	return z * cz;
}

void grille_creer(int width, int height) {
	/* TODO : allouer le tableau à deux dimensions : */
	grille = calloc(width, height);
	grille_largeur = width;
	grille_hauteur = height;
}

int in_grille(int x, int y) {
	/* TODO : vérifier si deux coordonnées sont dans la grille : */
	return 0;
}

void creuser(int x, int y) {
	/* TODO : corriger les erreurs de segmentation : */
	if(! in_grille(x, y)) return ;
	if(grille[x][y] != '#') return ;
	int link4 = 0;
	int link8 = 0;
	int i, j;
	int dx = 0, dy = 0;
	int tmp;
	for(i = -1; i <= 1; ++i) {
		for(j = -1; j <= 1; ++j) {
			if(! in_grille(x + i, y + j)) continue;
			if(i == j) continue;
			if(grille[x + i][y + j] == '.') ++link8;
			if(abs(i) + abs(j) != 1) continue;
			if(grille[x + i][y + j] == '.') ++link4;
		}
	}
	
	if(link4 > 1) return ;
	if(link8 > 2) return ;
	
	grille[x][y] = '.';
	
	/* TODO : améliorer les performances : */
	int perm[4] = {0, 1, 2, 3};
	for(i = 0; i < 20; ++i) {
		int a = rand() % 4, b = rand() % 4;
		tmp = perm[a];
		perm[a] = perm[b];
		perm[b] = tmp;
	}
	for(i = 0; i < 4; ++i) {
		switch(perm[i]) {
			case 0 : dx = 1; dy = 0; break;
			case 1 : dx = 0; dy = 1; break;
			case 2 : dx = -1; dy = 0; break;
			case 3 : dx = 0; dy = -1; break;
		}
		creuser(x + dx, y + dy);
	}
}

void grille_generer(int width, int height) {
	grille_creer(width, height);
	/* TODO : mettre tous les éléments de la grille à '#' .*/
	/* TODO : améliorer les tailles de grilles : */
	creuser(player_x, player_y);
	exit_x = rand() % width;
	exit_y = rand() % height;
}

void init() {
	player_x = grille_largeur / 2;
	player_y = grille_hauteur / 2;
	clock_t start, end;
	start = clock();
	grille_generer(grille_largeur, grille_hauteur);
	end = clock();
	printf("Génération d'une grille %dx%d en %g s\n", grille_largeur, grille_hauteur, (double)(end - start) / CLOCKS_PER_SEC);
}

int check_finish() {
	/* TODO : indiquer si le joueur a atteint la sortie. */
	/* TODO : générer le niveau suivant si terminé. */
	return 0;
}

int get_grille(int x, int y) {
	/* TODO : renvoyer l'élément présent à la coordonnée (mur ou chemin) */
	return (rand() % 2) ? '#' : '.';
}

int can_move(int x, int y) {
	/* TODO : valider ou non un déplacement vers des coordonnées. */
	return 1;
}

void afficher_grille() {
	/* TODO : optimiser l'affichage. */
	int x, y;
	for(x = 0; x < grille_largeur; ++x) {
		for(y = 0; y < grille_hauteur; ++y) {
			switch(get_grille(x, y)) {
				case '#' : boxRGBA(ecran, 
					ecran_depuis_camera_x(x - 0.5), ecran_depuis_camera_y(y - 0.5), 
					ecran_depuis_camera_x(x + 0.5), ecran_depuis_camera_y(y + 0.5),
					51, 51, 51, 255); break;
				case '.' : boxRGBA(ecran, 
					ecran_depuis_camera_x(x - 0.5), ecran_depuis_camera_y(y - 0.5), 
					ecran_depuis_camera_x(x + 0.5), ecran_depuis_camera_y(y + 0.5),
					204, 204, 204, 255); break;
				default : boxRGBA(ecran, 
					ecran_depuis_camera_x(x - 0.5), ecran_depuis_camera_y(y - 0.5), 
					ecran_depuis_camera_x(x + 0.5), ecran_depuis_camera_y(y + 0.5),
					25, 25, 25, 255); break;
			}
		}
	}
}

void affichage() {
	/* Remplissage de l'écran par un gris foncé uniforme : */
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
	afficher_grille();
	filledCircleRGBA(ecran, 
		ecran_depuis_camera_x(player_x), ecran_depuis_camera_y(player_y), 
		ecran_depuis_camera_z(0.5),
		25, 153, 25, 255);
	filledCircleRGBA(ecran, 
		ecran_depuis_camera_x(exit_x), ecran_depuis_camera_y(exit_y), 
		ecran_depuis_camera_z(0.5),
		25, 153, 153, 255);
}

int main(int argc, char * argv[]) {
	if(argc >= 3) {
		grille_largeur = atoi(argv[1]);
		grille_hauteur = atoi(argv[2]);
	}
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
	init();
	
	int active = 1;
	SDL_Event event;
	int refresh = 1;
	int right_grab = 0;
	
	/* Placement du joueur au centre de la fenêtre : */
	
	cx = grille_largeur / 2;
	cy = grille_hauteur / 2;
	cz = 5;
	
	SDL_EnableKeyRepeat(50, 50);
	
	while(active) {
		
		if(refresh) {
			affichage();
			SDL_Flip(ecran);
			refresh = 0;
		}
		
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
							cx = player_x;
							cy = player_y;
							refresh = 1;
						} break;
						
						case SDLK_z :
						case SDLK_UP : {
							if(can_move(player_x, player_y - 1)) {
								--player_y;
								refresh = 1;
								if(ecran_depuis_camera_y(player_y) < 0) {
									cy -= camera_depuis_ecran_z(hauteur);
								}
							}
						} break;
						
						case SDLK_s :
						case SDLK_DOWN : {
							if(can_move(player_x, player_y + 1)) {
								++player_y;
								refresh = 1;
								if(ecran_depuis_camera_y(player_y) > hauteur) {
									cy += camera_depuis_ecran_z(hauteur);
								}
							}
						} break;
						
						case SDLK_q :
						case SDLK_LEFT : {
							if(can_move(player_x - 1, player_y)) {
								--player_x;
								refresh = 1;
								if(ecran_depuis_camera_x(player_x) < 0) {
									cx -= camera_depuis_ecran_z(largeur);
								}
							}
						} break;
						
						case SDLK_d :
						case SDLK_RIGHT : {
							if(can_move(player_x + 1, player_y)) {
								++player_x;
								refresh = 1;
								if(ecran_depuis_camera_x(player_x) > largeur) {
									cx += camera_depuis_ecran_z(largeur);
								}
							}
						} break;
					}
				} break;
				
				case SDL_MOUSEBUTTONDOWN : {
					switch(event.button.button) {
						case SDL_BUTTON_WHEELUP : {
							cz *= 0.8;
							if(cz < 1e-9) {
								cz = 1e-9;
							}
							refresh = 1;
						} break;
						
						case SDL_BUTTON_WHEELDOWN : {
							cz /= 0.8;
							if(cz > 1e9) {
								cz = 1e9;
							}
							refresh = 1;
						} break;
						
						case SDL_BUTTON_RIGHT : {
							right_grab = 1;
						} break;
					}
				} break;
				
				case SDL_MOUSEBUTTONUP : {
					switch(event.button.button) {
						case SDL_BUTTON_RIGHT : {
							right_grab = 0;
						} break;
					}
				} break;
				
				case SDL_MOUSEMOTION : {
					if(right_grab) {
						cx += camera_depuis_ecran_z(-event.motion.xrel);
						cy += camera_depuis_ecran_z(-event.motion.yrel);
						refresh = 1;
					}
				} break;
			}
		}
		
		if(check_finish()) {
			cx = player_x;
			cy = player_y;
			refresh = 1;
		}
		
		SDL_Delay(1000 / 60);
	}
	
	/* TODO : libérer grille. */
	
	SDL_FreeSurface(ecran);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}