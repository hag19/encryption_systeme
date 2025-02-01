#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 600;
const char * titre = "ESGI spheres";

const int spheres_count = 4;
double temps = 0;
const int pixel_size = 2;

double camera_position_x = 0.;
double camera_position_y = 0.;
double camera_position_z = -5.;

/* Implicite : 
double camera_direction_x = 0.;
double camera_direction_y = 0.;
double camera_direction_z = 1.;
*/

double sphere_intersection(double start_x, double start_y, double start_z, double direction_x, double direction_y, double direction_z, double center_x, double center_y, double center_z, double radius) {
	/* TODO : renvoyer le décalage t à appliquer (start + t * direction) pour toucher la sphere de centre center et rayon radius */
	/* TODO : s'il n'y a pas intersection, renvoyer une grande valeur négative. */
	return 0.;
}

double intensity(double x, double y, double z, double center_x, double center_y, double center_z) {
	/* TODO : calculer normale (P - C) / norme(P - C) */
	/* TODO : définir une direction de lumière ambiante */
	/* TODO : calculer le produit scalaire de la normale et la direction de la lumière */
	return 0.5;
}

int nearest(int first_sphere, double first_offset, int second_sphere, double second_offset) {
	/* TODO : déterminer la sphère visible la plus proche */
	return (rand() % 2) ? first_sphere : second_sphere;
}

/* TODO : coder une couleur RGBA sur un entier */

unsigned int sphere_color(int id) {
	unsigned char r, g, b, a;
	a = 255;
	r = (id * 1337 + 127) % 256;
	g = (id * 133712 + 127) % 256;
	b = (id * 13371234 + 127) % 256;
	return 0 /* TODO : renvoyer la couleur RGBA */;
}

double sphere_x(int id) {
	return sin(id * 1274 + 0.2 * temps);
}

double sphere_y(int id) {
	return sin(id * 127478 + (0.3 + id * 0.1) * temps);
}

double sphere_z(int id) {
	return sin(id * 8899 + 0.5 * temps);
}

double sphere_r(int id) {
	return 0.375 + 0.25 * sin(id * 855) + 0.1 * sin(temps);
}

unsigned int pixel_color(int x, int y) {
	unsigned char r, g, b, a;
	double offset_x = x / (largeur / 2.) - 1.;
	double offset_y = y / (hauteur / 2.) - 1.;
	offset_x *= ((float)largeur / hauteur);
	
	int nearest_sphere;
	double nearest_t;
	int i;
	double t;
	for(i = 0; i < spheres_count; ++i) {
		t = sphere_intersection(camera_position_x + offset_x, camera_position_y + offset_y, camera_position_z, 0., 0., 1., sphere_x(i), sphere_y(i), sphere_z(i), sphere_r(i));
		if(i == 0) {
			nearest_sphere = i;
			nearest_t = t;
		} else {
			nearest_sphere = nearest(nearest_sphere, nearest_t, i, t);
			if(nearest_sphere == i) {
				nearest_t = t;
			}
		}
	}
	
	if(nearest_t < 0.) {
		return 0;
	}
	unsigned int color = sphere_color(nearest_sphere);
	/* TODO : récupérer la couleur RGB */
	r = 0;
	g = 0;
	b = 0;
	double value = intensity(camera_position_x + offset_x, camera_position_y + offset_y, camera_position_z + nearest_t, sphere_x(nearest_sphere), sphere_y(nearest_sphere), sphere_z(nearest_sphere));
	a = 255;
	r = value * r;
	g = value * g;
	b = value * b;
	return 0 /* TODO : renvoyer la couleur RGBA */;
}

void affichage(SDL_Surface * ecran) {
	/* Remplissage de l'écran par un gris foncé uniforme : */
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
	/* Affichage du joueur : */
	int x, y;
	unsigned int color;
	unsigned char r, g, b, a;
	SDL_Rect pixel;
	for(x = 0; x < largeur; x += pixel_size) {
		for(y = 0; y < hauteur; y += pixel_size) {
			color = pixel_color(x + pixel_size / 2., y + pixel_size / 2.);
			/* TODO : récupérer la couleur RGB */
			r = 0;
			g = 0;
			b = 0;
			a = 0;
			if(a < 127) continue;
			pixel.x = x;
			pixel.y = y;
			pixel.w = pixel_size;
			pixel.h = pixel_size;
			SDL_FillRect(ecran, &pixel, SDL_MapRGB(ecran->format, r, g, b));
		}
	}
}

int main() {
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
	int FPS_delay = 1000 / 60;
	int delay;
	
	while(active) {
		
		temps = SDL_GetTicks() / 1000.;
		delay = SDL_GetTicks();
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
			}
		}
		
		delay = FPS_delay - (SDL_GetTicks() - delay);
		if(delay > 0) {
			SDL_Delay(delay);
		}
	}
	
	SDL_FreeSurface(ecran);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}