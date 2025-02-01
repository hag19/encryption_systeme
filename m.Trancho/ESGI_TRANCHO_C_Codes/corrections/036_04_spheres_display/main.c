/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 36.
 */

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

const int spheres_count = 8;
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
  double direction_norm_square = pow(direction_x, 2.) + pow(direction_y, 2.) + pow(direction_z, 2.);
  double positions_norm_square = pow(start_x - center_x, 2.) + pow(start_y - center_y, 2.) + pow(start_z - center_z, 2.);
  double a = direction_norm_square;
  double b = 2. * (direction_x * (start_x - center_x) + direction_y * (start_y - center_y) + direction_z * (start_z - center_z));
  double c = positions_norm_square - radius * radius;
  double d = b * b - 4 * a * c;
  if(d < 0) {
    return -1e100;
  }
  double x1 = (-b - sqrt(d)) / (2 * a);
  double x2 = (-b + sqrt(d)) / (2 * a);
  if(x1 > 0 && x2 > 0) {
    return fmin(x1, x2);
  } else if(x1 > 0) {
    return x1;
  } else if(x2 > 0) {
    return x2;
  }
  return -1e100;
}

const unsigned int R_CHANNEL = 0x01000000;
const unsigned int G_CHANNEL = 0x00010000;
const unsigned int B_CHANNEL = 0x00000100;
const unsigned int A_CHANNEL = 0x00000001;

double intensity(double x, double y, double z, double center_x, double center_y, double center_z) {
  x -= center_x;
  y -= center_y;
  z -= center_z;
  double norm = sqrt(x * x + y * y + z * z);
  if(norm < 1e-9) {
    return 0.5;
  }
  x /= norm;
  y /= norm;
  z /= norm;
  double lx = 1.;
  double ly = -1.;
  double lz = -1.;
  norm = sqrt(lx * lx + ly * ly + lz * lz);
  lx /= norm;
  ly /= norm;
  lz /= norm;
  return fmax(pow(0.5 * (x * lx + y * ly + z * lz) + 0.5, 0.75), 0.25);
}

int nearest(int first_sphere, double first_offset, int second_sphere, double second_offset) {
  if(first_offset > 0 && second_offset > 0) {
    return (first_offset < second_offset) ? first_sphere : second_sphere;
  } else if(first_offset > 0) {
    return first_sphere;
  } else if(second_offset > 0) {
    return second_sphere;
  }
  return (first_offset < second_offset) ? first_sphere : second_sphere;
}

unsigned int sphere_color(int id) {
  unsigned char r, g, b, a;
  a = 255;
  r = (id * 1337 + 127) % 256;
  g = (id * 133712 + 127) % 256;
  b = (id * 13371234 + 127) % 256;
  return r * R_CHANNEL + g * G_CHANNEL + b * B_CHANNEL + a * A_CHANNEL;
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
  r = (color / R_CHANNEL) % 256;
  g = (color / G_CHANNEL) % 256;
  b = (color / B_CHANNEL) % 256;
  double value = intensity(camera_position_x + offset_x, camera_position_y + offset_y, camera_position_z + nearest_t, sphere_x(nearest_sphere), sphere_y(nearest_sphere), sphere_z(nearest_sphere));
  a = 255;
  r = value * r;
  g = value * g;
  b = value * b;
  return r * R_CHANNEL + g * G_CHANNEL + b * B_CHANNEL + a * A_CHANNEL;
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
      r = (color / R_CHANNEL) % 256;
      g = (color / G_CHANNEL) % 256;
      b = (color / B_CHANNEL) % 256;
      a = (color / A_CHANNEL) % 256;
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