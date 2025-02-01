/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 45.
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
  return ((x - cx) * largeur / 2) / cz + largeur / 2;
}

int ecran_depuis_camera_y(float y) {
  return ((y - cy) * hauteur / 2) / cz + hauteur / 2;
}

float ecran_depuis_camera_z(int z) {
  return (z * largeur / 2.) / cz;
}

float camera_depuis_ecran_x(int x) {
  return 2. * ((x - largeur / 2) * cz) / largeur + cx;
}

float camera_depuis_ecran_y(int y) {
  return 2. * ((y - hauteur / 2) * cz) / hauteur + cy;
}

float camera_depuis_ecran_z(int z) {
  return (2 * z * cz) / largeur;
}

const unsigned int R_CHANNEL = 0x01000000;
const unsigned int G_CHANNEL = 0x00010000;
const unsigned int B_CHANNEL = 0x00000100;
const unsigned int A_CHANNEL = 0x00000001;

int implicit_distance(double iso) {
  double v = 0.5 * cos(iso * M_PI * 2.) + 0.5;
  if(iso < 0) {
    v = 0.5 + 0.5 * v;
  }
  unsigned char r, g, b, a;
  a = 255;
  if(fabs(v) > 1 - 1e-2 && fabs(iso) < 0.1) {
    r = 0;
    g = 255;
    b = 0;
  } else if(fabs(v) > 1 - 1e-2) {
    r = 127;
    g = 127;
    b = 127;
  } else if(iso < 0) {
    r = 255;
    g = 0;
    b = 0;
  } else {
    r = 0;
    g = 0;
    b = 255;
  }
  r = 0.75 * v * r + 63;
  g = 0.75 * v * g + 63;
  b = 0.75 * v * b + 63;
  return r * R_CHANNEL + g * G_CHANNEL + b * B_CHANNEL + a * A_CHANNEL;
}

int simple_distance(double iso) {
  double v = 1;
  unsigned char r, g, b, a;
  a = 255;
  r = 255;
  g = 255;
  b = 255;
  if(iso > 0) v = 0;
  r = 0.75 * v * r + 63;
  g = 0.75 * v * g + 63;
  b = 0.75 * v * b + 63;
  return r * R_CHANNEL + g * G_CHANNEL + b * B_CHANNEL + a * A_CHANNEL;
}

int factal_color(double coeff) {
  double v = 1;
  unsigned char r, g, b, a;
  a = 255;
  r = 255;
  g = 255;
  b = 255;
  r *= coeff;
  g *= coeff;
  b *= coeff;
  return r * R_CHANNEL + g * G_CHANNEL + b * B_CHANNEL + a * A_CHANNEL;
}

int draw_distance_circle(double x, double y) {
  return implicit_distance(sqrt(x * x + y * y) - 1);
}

int draw_distance_square(double x, double y) {
  if(fabs(x) > 1 && fabs(y) > 1) {
    double d = x * x + y * y - 2 * (fabs(x) + fabs(y)) + 2;
    return implicit_distance(sqrt(d));
  }
  return implicit_distance(fmax(fabs(x), fabs(y)) - 1);
}

int draw_circle(double x, double y) {
  return simple_distance(sqrt(x * x + y * y) - 1);
}

int draw_square(double x, double y) {
  return simple_distance(fmax(fabs(x), fabs(y)) - 1);
}

int draw_mandelbrot(double x, double y) {
  double cx = x, cy = y;
  double nx, ny;
  int i;
  for(i = 0; i < max_iter && x * x + y * y < 4; ++i) {
    nx = x * x - y * y + cx;
    ny = 2 * x * y + cy;
    x = nx;
    y = ny;
  }
  return factal_color((double)i / max_iter);
}

int draw_julia(double x, double y) {
  double cx = jx, cy = jy;
  double nx, ny;
  int i;
  for(i = 0; i < max_iter && x * x + y * y < 4; ++i) {
    nx = x * x - y * y + cx;
    ny = 2 * x * y + cy;
    x = nx;
    y = ny;
  }
  return factal_color((double)i / max_iter);
}

int draw_burning_ship(double x, double y) {
  double cx = x, cy = y;
  double nx, ny;
  int i;
  x = y = 0;
  for(i = 0; i < max_iter && x * x + y * y < 4; ++i) {
    nx = x * x - y * y + cx;
    ny = 2 * fabs(x) * fabs(y) + cy;
    x = nx;
    y = ny;
  }
  return factal_color((double)i / max_iter);
}

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

int color_newton(double x, double y, double coeff) {
  double sx, sy;
  double w, sw = 0;
  double r = 0, g = 0, b = 0;
  double cr, cg, cb;
  int i;
  for(i = 0; i < newton_n; ++i) {
    sx = cos(i * 2. * M_PI / newton_n);
    sy = sin(i * 2. * M_PI / newton_n);
    w = 1 / (1e-6 + fabs(sx - x) + fabs(sy - y));
    switch(i % 6) {
      case 0 : cr = 1; cg = 0; cb = 0; break;
      case 1 : cr = 0; cg = 1; cb = 0; break;
      case 2 : cr = 0; cg = 0; cb = 1; break;
      case 3 : cr = 1; cg = 1; cb = 0; break;
      case 4 : cr = 0; cg = 1; cb = 1; break;
      case 5 : cr = 1; cg = 0; cb = 1; break;
    }
    r += w * cr;
    g += w * cg;
    b += w * cb;
    sw += w;
  }
  unsigned char vr, vg, vb, va;
  va = 255;
  vr = coeff * 255 * (r / sw);
  vg = coeff * 255 * (g / sw);
  vb = coeff * 255 * (b / sw);
  return vr * R_CHANNEL + vg * G_CHANNEL + vb * B_CHANNEL + va * A_CHANNEL;
}

int draw_newton(double x, double y) {
  double nx, ny;
  double znx, zny;
  double zn1x, zn1y;
  int i;
  for(i = 0; i < max_iter && fabs(x * x + y * y - 1) > 1e-6; ++i) {
    complex_pow(x, y, newton_n, &znx, &zny);
    complex_pow(x, y, newton_n - 1, &zn1x, &zn1y);
    znx -= 1;
    complex_div(znx, zny, zn1x, zn1y, &nx, &ny);
    x -= nx / newton_n;
    y -= ny / newton_n;
  }
  return color_newton(x, y, 1. / log(1 + i));
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