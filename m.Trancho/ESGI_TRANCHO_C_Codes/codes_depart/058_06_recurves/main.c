#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 800;
const char * titre = "ESGI graph";
const int functions_count = 9;

/* Position de la caméra et échelle de la vue : */
float cx, cy, cz;

int current_function = 0;
int iterations = 2;
int segments = 1;

void (*fonction(int id))(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a);

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

void affichage(SDL_Surface * ecran) {
	/* Remplissage de l'écran par un gris foncé uniforme : */
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
	
	void (*line)(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) = fonction(current_function);
	
	double scale = 10;
	if(segments <= 1) {
		line(ecran,
			ecran_depuis_camera_x(-scale), ecran_depuis_camera_y(0), 
			ecran_depuis_camera_x(scale), ecran_depuis_camera_y(0),
			iterations,
			255, 255, 255, 255);
	} else {
		int i;
		for(i = 0; i < segments; ++i) {
			line(ecran,
				ecran_depuis_camera_x(scale * cos(i * 2 * M_PI / segments)), ecran_depuis_camera_y(scale * sin(i * 2 * M_PI / segments)), 
				ecran_depuis_camera_x(scale * cos((i + 1) * 2 * M_PI / segments)), ecran_depuis_camera_y(scale * sin((i + 1) * 2 * M_PI / segments)), 
				iterations,
				255, 255, 255, 255);
		}
	}
	
	char buffer[1024];
	stringRGBA(ecran, 10, 10, fonction_name(current_function), 204, 204, 153, 255);
	sprintf(buffer, "Iterations : %d", iterations);
	stringRGBA(ecran, 10, 25, buffer, 204, 204, 153, 255);
	sprintf(buffer, "Segments : %d", segments);
	stringRGBA(ecran, 10, 40, buffer, 204, 204, 153, 255);
}

void flocon_koch(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
	/* TODO : flocon de Koch */
	lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
}

void courbe_koch(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    /* TODO : courbe de Koch */
	lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
}

void courbe_koch_alt(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    /* TODO : courbe de Koch version alternée */
	lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
}

void courbe_cesaro(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    /* TODO : fractale de Cesaro */
	lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
}

void courbe_dragon(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    /* TODO : courbe du Dragon */
	lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
}

void courbe_gosper(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
	/* TODO : courbe de Gosper */
	lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
}

void courbe_hilbert(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
	/* TODO : courbe de Hilbert */
	lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
}

void tapis_sierpinski(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    int nx = (ey - sy);
    int ny = -(ex - sx);
    Sint16 xs[] = {
    	sx,
    	sx + nx,
    	ex + nx,
    	ex
    };
    Sint16 ys[] = {
    	sy,
    	sy + ny,
    	ey + ny,
    	ey
    };
    filledPolygonRGBA(ecran, xs, ys, 4, r / 10, g / 10, b / 10, a);
    /* TODO : tapis de Spierpinski */
}

void triangle_sierpinski(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    int nx = (ey - sy);
    int ny = -(ex - sx);
	Sint16 xs[] = {
    	sx,
    	0.5 * (sx + ex) + 0.87 * nx,
    	ex
    };
    Sint16 ys[] = {
    	sy,
    	0.5 * (sy + ey) + 0.87 * ny,
    	ey
    };
    filledPolygonRGBA(ecran, xs, ys, 3, r / 10, g / 10, b / 10, a);
    /* TODO : triangle de Spierpinski */
}

const char * fonction_name(int id) {
	switch(id) {
		case 1 : return "Courbe de Koch";
		case 2 : return "Fractale Cesaro";
		case 3 : return "Courbe de Koch alternee";
		case 4 : return "Courbe du Dragon";
		case 5 : return "Courbe de Gosper";
		case 6 : return "Courbe de Hilbert";
		case 7 : return "Tapis de Sierpinski";
		case 8 : return "Triangle de Sierpinski";
		default : return "Flocon de Koch";
	}
}

void (*fonction(int id))(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
	switch(id) {
		case 1 : return courbe_koch;
		case 2 : return courbe_cesaro;
		case 3 : return courbe_koch_alt;
		case 4 : return courbe_dragon;
		case 5 : return courbe_gosper;
		case 6 : return courbe_hilbert;
		case 7 : return tapis_sierpinski;
		case 8 : return triangle_sierpinski;
		default : return flocon_koch;
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
						
						case SDLK_RIGHT : {
							iterations++;
							refresh = 1;
						} break;
						
						case SDLK_LEFT : {
							iterations--;
							refresh = 1;
						} break;
						
						case SDLK_a : {
							segments++;
							refresh = 1;
						} break;
						
						case SDLK_q : {
							segments--;
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