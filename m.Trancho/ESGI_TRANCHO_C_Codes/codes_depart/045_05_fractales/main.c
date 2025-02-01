#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 800;
const char * titre = "ESGI draw";
const int functions_count = 8;
int resolution = 1;

double jx = 0, jy = 0;
int max_iter = 25;
int newton_n = 3;

/* Position de la caméra et échelle de la vue : */
float cx, cy, cz;

int current_function = 0;

int (* fonction(int id))(double x, double y);

const char * fonction_name(int id);

int ecran_depuis_camera_x(float x) {
	/* TODO */
	return x;
}

int ecran_depuis_camera_y(float y) {
	/* TODO */
	return y;
}

float ecran_depuis_camera_z(int z) {
	/* TODO */
	return z;
}

float camera_depuis_ecran_x(int x) {
	/* TODO */
	return x;
}

float camera_depuis_ecran_y(int y) {
	/* TODO */
	return y;
}

float camera_depuis_ecran_z(int z) {
	/* TODO */
	return z;
}

const unsigned int R_CHANNEL = 0x01000000;
const unsigned int G_CHANNEL = 0x00010000;
const unsigned int B_CHANNEL = 0x00000100;
const unsigned int A_CHANNEL = 0x00000001;

/* Multiplication de nombres complexes : */
/* utilisation : */
/* double ax, ay; */
/* double bx, by; */
/* double rx, ry; */
/* complex_mul(ax, ay, bx, by, &rx, &ry); */
void complex_mul(double a, double b, double x, double y, double * rx, double * ry) {
	*rx = a * x - b * y;
	*ry = a * y + b * x;
}

/* Division de nombres complexes : */
/* utilisation : */
/* double ax, ay; */
/* double bx, by; */
/* double rx, ry; */
/* complex_div(ax, ay, bx, by, &rx, &ry); */
void complex_div(double a, double b, double x, double y, double * rx, double * ry) {
	double norm = x * x + y * y;
	complex_mul(a, b, x, -y, rx, ry);
	*rx /= norm;
	*ry /= norm;
}

/* Puissance de nombres complexes : */
/* utilisation : */
/* double ax, ay; */
/* int n; */
/* double rx, ry; */
/* complex_pow(ax, ay, n, &rx, &ry); */
void complex_pow(double a, double b, int n, double * rx, double * ry) {
	*rx = 1;
	*ry = 0;
	while(n > 0) {
		if(n % 2 == 1) {
			complex_mul(*rx, *ry, a, b, rx, ry);
		}
		complex_mul(a, b, a, b, &a, &b);
		n /= 2;
	}
}

int draw_distance_circle(double x, double y) {
	/* TODO : calculer distance à un cercle */
	return 0xff;
}

int draw_distance_square(double x, double y) {
	/* TODO : calculer distance à un carré */
	return 0xff;
}

int draw_circle(double x, double y) {
	/* TODO : colorer si intérieur d'un cercle */
	return 0xff;
}

int draw_square(double x, double y) {
	/* TODO : colorer si intérieur d'un carré */
	return 0xff;
}

int draw_mandelbrot(double x, double y) {
	/* TODO : dessiner la fractale de Mandelbrot. */
	/* Elle est donnée par la relation suivante : */
	/* z_(n + 1) = z_n * z_n + c */
	/* avec z_0 = 0, c = (x, y). */
	/* l'afficher si elle ne diverge pas */
	/* (vérifier sqrt(x * x + y * y) < 2) */
	return 0xff;
}

int draw_julia(double x, double y) {
	/* TODO : dessiner la fractale de Julia */
	/* Elle est donnée par la relation suivante : */
	/* z_(n + 1) = z_n * z_n + c */
	/* avec z_0 = (x, y), c = (jx, jy). */
	/* l'afficher si elle ne diverge pas */
	/* (vérifier sqrt(x * x + y * y) < 2) */
	return 0xff;
}

int draw_burning_ship(double x, double y) {
	/* TODO : dessiner la fractale du Burning ship */
	/* Elle est donnée par la relation suivante : */
	/* z_(n + 1) = (abs(Re(z_n)) + i abs(Im(z_n))) ** 2 + c */
	/* avec z_0 = (0, 0), c = (x, y). */
	/* l'afficher si elle ne diverge pas */
	/* (vérifier sqrt(x * x + y * y) < 2) */
	return 0xff;
}

int draw_newton(double x, double y) {
	int i;
	/* TODO : dessiner la fractale de la racine n-ème de l'unité */
	/* selon convergence de la méthode de Newton. */
	/* Elle est donnée par la relation suivante : */
	/* z_(i + 1) = z_i - (z_i ** n - 1) / (n z_i ** (n - 1)) */
	/* avec z_0 = (x, y). */
	/* la méthode converge vers une des solutions suivantes : */
	/* {(cos(2 k pi / n), sin(2 k pi / n)) pour k entier entre 0 et n - 1} */
	return 0xff;
}

void affichage(SDL_Surface * ecran) {
	/* Remplissage de l'écran par un gris foncé uniforme : */
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
	unsigned int color;
	unsigned char r, g, b, a;
	SDL_Rect pixel;
	double x, y;
	int i, j;
	for(i = 0; i < largeur; i += resolution) {
		for(j = 0; j < hauteur; j += resolution) {
			x = ecran_depuis_camera_x(i + 0.5 * resolution);
			y = ecran_depuis_camera_y(j + 0.5 * resolution);
			color = fonction(current_function)(camera_depuis_ecran_x(i), camera_depuis_ecran_y(j));
			r = (color / R_CHANNEL) % 256;
			g = (color / G_CHANNEL) % 256;
			b = (color / B_CHANNEL) % 256;
			a = (color / A_CHANNEL) % 256;
			if(a < 127) continue;
			pixel.x = i;
			pixel.y = j;
			pixel.w = resolution;
			pixel.h = resolution;
			SDL_FillRect(ecran, &pixel, SDL_MapRGB(ecran->format, r, g, b));
		}
	}
	
	stringRGBA(ecran, 10, 10, fonction_name(current_function), 204, 204, 153, 255);
	char buffer[1024];
	sprintf(buffer, "Iterations : %d", max_iter);
	stringRGBA(ecran, 10, 25, buffer, 204, 204, 153, 255);
}

const char * fonction_name(int id) {
	switch(id) {
		case 1 : return "carre";
		case 2 : return "distance cercle";
		case 3 : return "distance carre";
		case 4 : return "Mandelbrot";
		case 5 : return "Julia";
		case 6 : return "Burning ship";
		case 7 : return "Newton";
		default : return "cercle";
	}
}

int (* fonction(int id))(double x, double y) {
	switch(id) {
		case 1 : return draw_square;
		case 2 : return draw_distance_circle;
		case 3 : return draw_distance_square;
		case 4 : return draw_mandelbrot;
		case 5 : return draw_julia;
		case 6 : return draw_burning_ship;
		case 7 : return draw_newton;
		default : return draw_circle;
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
	
	/* Placement du joueur au centre de la fenêtre : */
	
	cx = 0;
	cy = 0;
	cz = 10;
	
	int active = 1;
	SDL_Event event;
	int grab = 0;
	int refresh = 1;
	
	while(active) {
		
		if(refresh) {
			affichage(ecran);
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
						
						case SDLK_j : {
							jx -= 0.025;
							refresh = 1;
						} break;
						case SDLK_l :  {
							jx += 0.025;
							refresh = 1;
						} break;
						case SDLK_i :  {
							jy += 0.025;
							refresh = 1;
						} break;
						case SDLK_k :  {
							jy -= 0.025;
							refresh = 1;
						} break;
						
						case SDLK_y :  {
							max_iter += 5;
							refresh = 1;
						} break;
						case SDLK_h :  {
							max_iter -= 5;
							refresh = 1;
						} break;
						
						case SDLK_t :  {
							newton_n++;
							refresh = 1;
						} break;
						case SDLK_g :  {
							newton_n--;
							refresh = 1;
						} break;
					}
				} break;
				
				case SDL_KEYUP : {
					switch(event.key.keysym.sym) {
						case SDLK_UP : {
							current_function = (current_function + 1) % functions_count;
							refresh = 1;
						} break;
						
						case SDLK_DOWN : {
							current_function = (current_function + functions_count - 1) % functions_count;
							refresh = 1;
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
						
						case SDL_BUTTON_LEFT : {
							grab = 1;
						} break;
					}
				} break;
				
				case SDL_MOUSEBUTTONUP : {
					switch(event.button.button) {
						case SDL_BUTTON_LEFT : {
							grab = 0;
						} break;
					}
				} break;
				
				case SDL_MOUSEMOTION : {
					if(grab) {
						cx += camera_depuis_ecran_z(-event.motion.xrel);
						cy += camera_depuis_ecran_z(-event.motion.yrel);
						refresh = 1;
					}
				} break;
			}
		}
		
		SDL_Delay(1000 / 60);
	}
	
	SDL_FreeSurface(ecran);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}