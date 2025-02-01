/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 58.
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
    if(n <= 1) {
        lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
        return;
    }
    int nx = (ey - sy);
    int ny = -(ex - sx);
    flocon_koch(ecran, sx, sy, sx + (ex - sx) / 3, sy + (ey - sy) / 3, n - 1, r, g, b, a);
    flocon_koch(ecran, sx + (ex - sx) / 3, sy + (ey - sy) / 3, 0.5 * (sx + ex) + 0.25 * nx, 0.5 * (sy + ey) + 0.25 * ny, n - 1, r, g, b, a);
    flocon_koch(ecran, 0.5 * (sx + ex) + 0.25 * nx, 0.5 * (sy + ey) + 0.25 * ny, sx + 2 * (ex - sx) / 3, sy + 2 * (ey - sy) / 3, n - 1, r, g, b, a);
    flocon_koch(ecran, sx + 2 * (ex - sx) / 3, sy + 2 * (ey - sy) / 3, ex, ey, n - 1, r, g, b, a);
}

void courbe_koch(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    if(n <= 1) {
        lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
        return;
    }
    int nx = (ey - sy);
    int ny = -(ex - sx);
    courbe_koch(ecran, sx, sy, sx + (ex - sx) / 3, sy + (ey - sy) / 3, n - 1, r, g, b, a);
    courbe_koch(ecran, sx + (ex - sx) / 3, sy + (ey - sy) / 3, sx + (ex - sx) / 3 + nx / 3, sy + (ey - sy) / 3 + ny / 3, n - 1, r, g, b, a);
    courbe_koch(ecran, sx + (ex - sx) / 3 + nx / 3, sy + (ey - sy) / 3 + ny / 3, sx + 2 * (ex - sx) / 3 + nx / 3, sy + 2 * (ey - sy) / 3 + ny / 3, n - 1, r, g, b, a);
    courbe_koch(ecran, sx + 2 * (ex - sx) / 3 + nx / 3, sy + 2 * (ey - sy) / 3 + ny / 3, sx + 2 * (ex - sx) / 3, sy + 2 * (ey - sy) / 3, n - 1, r, g, b, a);
    courbe_koch(ecran, sx + 2 * (ex - sx) / 3, sy + 2 * (ey - sy) / 3, ex, ey, n - 1, r, g, b, a);
}

void courbe_koch_alt(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    if(n <= 1) {
        lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
        return;
    }
    int nx = (ey - sy);
    int ny = -(ex - sx);
    courbe_koch_alt(ecran, sx, sy, sx + (ex - sx) / 4, sy + (ey - sy) / 4, n - 1, r, g, b, a);
    courbe_koch_alt(ecran, sx + (ex - sx) / 4, sy + (ey - sy) / 4, sx + (ex - sx) / 4 + nx / 4, sy + (ey - sy) / 4 + ny / 4, n - 1, r, g, b, a);
    courbe_koch_alt(ecran, sx + (ex - sx) / 4 + nx / 4, sy + (ey - sy) / 4 + ny / 4, sx + 2 * (ex - sx) / 4 + nx / 4, sy + 2 * (ey - sy) / 4 + ny / 4, n - 1, r, g, b, a);
    courbe_koch_alt(ecran, sx + 2 * (ex - sx) / 4 + nx / 4, sy + 2 * (ey - sy) / 4 + ny / 4, sx + 2 * (ex - sx) / 4 - nx / 4, sy + 2 * (ey - sy) / 4 - ny / 4, n - 1, r, g, b, a);
    courbe_koch_alt(ecran, sx + 2 * (ex - sx) / 4 - nx / 4, sy + 2 * (ey - sy) / 4 - ny / 4, sx + 3 * (ex - sx) / 4 - nx / 4, sy + 3 * (ey - sy) / 4 - ny / 4, n - 1, r, g, b, a);
    courbe_koch_alt(ecran, sx + 3 * (ex - sx) / 4 - nx / 4, sy + 3 * (ey - sy) / 4 - ny / 4, sx + 3 * (ex - sx) / 4, sy + 3 * (ey - sy) / 4, n - 1, r, g, b, a);
    courbe_koch_alt(ecran, sx + 3 * (ex - sx) / 4, sy + 3 * (ey - sy) / 4, ex, ey, n - 1, r, g, b, a);
}

void courbe_cesaro(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    if(n <= 1) {
        lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
        return;
    }
    int nx = (ey - sy);
    int ny = -(ex - sx);
    double biais = 0.05;
    double b1 = 1. + biais;
    double b2 = 2. - biais;
    courbe_cesaro(ecran, sx, sy, sx + (ex - sx) / 3, sy + (ey - sy) / 3, n - 1, r, g, b, a);
    courbe_cesaro(ecran, sx + (ex - sx) / 3, sy + (ey - sy) / 3, sx + b1 * (ex - sx) / 3 + nx / 3, sy + b1 * (ey - sy) / 3 + ny / 3, n - 1, r, g, b, a);
    courbe_cesaro(ecran, sx + b1 * (ex - sx) / 3 + nx / 3, sy + b1 * (ey - sy) / 3 + ny / 3, sx + b2 * (ex - sx) / 3 + nx / 3, sy + b2 * (ey - sy) / 3 + ny / 3, n - 1, r, g, b, a);
    courbe_cesaro(ecran, sx + b2 * (ex - sx) / 3 + nx / 3, sy + b2 * (ey - sy) / 3 + ny / 3, sx + 2 * (ex - sx) / 3, sy + 2 * (ey - sy) / 3, n - 1, r, g, b, a);
    courbe_cesaro(ecran, sx + 2 * (ex - sx) / 3, sy + 2 * (ey - sy) / 3, ex, ey, n - 1, r, g, b, a);
}

void courbe_dragon(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    if(n <= 1) {
        lineRGBA(ecran, sx, sy, ex, ey, r, g, b, a);
        return;
    }
    int nx = (ey - sy);
    int ny = -(ex - sx);
    courbe_dragon(ecran, sx, sy, 0.5 * (sx + ex) - 0.5 * nx, 0.5 * (sy + ey) - 0.5 * ny, n - 1, r, g, b, a);
    courbe_dragon(ecran, ex, ey, 0.5 * (sx + ex) - 0.5 * nx, 0.5 * (sy + ey) - 0.5 * ny, n - 1, r, g, b, a);
}

double tx;
double ty;
double tangle;

void Tortue_avancer(double value, SDL_Surface * ecran, int r, int g, int b, int a) {
  double x = tx, y = ty;
  tx += value * cos((tangle * M_PI) / 180.);
  ty += value * sin((tangle * M_PI) / 180.);
  lineRGBA(ecran, x, y, tx, ty, r, g, b, a);
}

void Tortue_tourner(int angle) {
  angle %= 360;
  tangle += angle;
  if(tangle < 0) tangle += 360;
  if(tangle > 360) tangle -= 360;
}

void courbe_gosper_rule_A(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a);
void courbe_gosper_rule_B(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a);

void courbe_gosper_rule_A(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a) {
  if(n <= 1) {
        Tortue_avancer(value, ecran, r, g, b, a);
        return;
    }
    value /= sqrt(7.);
    courbe_gosper_rule_A(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-60);
    courbe_gosper_rule_B(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-60);
    Tortue_tourner(-60);
    courbe_gosper_rule_B(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(60);
    courbe_gosper_rule_A(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(60);
    Tortue_tourner(60);
    courbe_gosper_rule_A(ecran, value, n - 1, r, g, b, a);
    courbe_gosper_rule_A(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(60);
    courbe_gosper_rule_B(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-60);
}

void courbe_gosper_rule_B(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a) {
  if(n <= 1) {
        Tortue_avancer(value, ecran, r, g, b, a);
        return;
    }
    value /= sqrt(7.);
    Tortue_tourner(60);
    courbe_gosper_rule_A(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-60);
    courbe_gosper_rule_B(ecran, value, n - 1, r, g, b, a);
    courbe_gosper_rule_B(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-60);
    Tortue_tourner(-60);
    courbe_gosper_rule_B(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-60);
    courbe_gosper_rule_A(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(60);
    Tortue_tourner(60);
    courbe_gosper_rule_A(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(60);
    courbe_gosper_rule_B(ecran, value, n - 1, r, g, b, a);
}

void courbe_gosper(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
  double norm = sqrt(pow(ex - sx, 2.) + pow(ey - sy, 2.));
    double angle = ((fabs(ey - sy) < 1e-9) ? 1 : ((ey - sy) / fabs(ey - sy))) * acos((ex - sx) / norm) * 180. / M_PI;
    tx = sx;
    ty = sy;
    tangle = angle + n * 19.11;
    courbe_gosper_rule_A(ecran, norm, n, r, g, b, a);
}

void courbe_hilbert_rule_L(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a);
void courbe_hilbert_rule_R(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a);

void courbe_hilbert_rule_L(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a) {
  
    if(n <= 1) {
        return;
    }
    Tortue_tourner(-90);
    courbe_hilbert_rule_R(ecran, value, n - 1, r, g, b, a);
    Tortue_avancer(value, ecran, r, g, b, a);
    Tortue_tourner(+90);
    courbe_hilbert_rule_L(ecran, value, n - 1, r, g, b, a);
    Tortue_avancer(value, ecran, r, g, b, a);
    courbe_hilbert_rule_L(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(+90);
    Tortue_avancer(value, ecran, r, g, b, a);
    courbe_hilbert_rule_R(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-90);
}

void courbe_hilbert_rule_R(SDL_Surface * ecran, double value, int n, int r, int g, int b, int a) {
    
    if(n <= 1) {
        return;
    }
    Tortue_tourner(+90);
    courbe_hilbert_rule_L(ecran, value, n - 1, r, g, b, a);
    Tortue_avancer(value, ecran, r, g, b, a);
    Tortue_tourner(-90);
    courbe_hilbert_rule_R(ecran, value, n - 1, r, g, b, a);
    Tortue_avancer(value, ecran, r, g, b, a);
    courbe_hilbert_rule_R(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(-90);
    Tortue_avancer(value, ecran, r, g, b, a);
    courbe_hilbert_rule_L(ecran, value, n - 1, r, g, b, a);
    Tortue_tourner(+90);
}

void courbe_hilbert(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
  double norm = sqrt(pow(ex - sx, 2.) + pow(ey - sy, 2.));
  double angle = ((fabs(ey - sy) < 1e-9) ? 1 : ((ey - sy) / fabs(ey - sy))) * acos((ex - sx) / norm) * 180. / M_PI;
    tx = sx;
    ty = sy;
    tangle = angle;
    courbe_hilbert_rule_L(ecran, norm / pow(2., n - 1), n, r, g, b, a);
}

void tapis_sierpinski_aux(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    int nx = (ey - sy);
    int ny = -(ex - sx);
    if(n <= 1) {
        return;
    }
    int i, j;
    for(i = 0; i < 3; ++i) {
      for(j = 0; j < 3; ++j) {
        if(i == 1 && j == 1) continue;
        tapis_sierpinski_aux(ecran,
          sx + ((i) / 3.) * (ex - sx) + ((j) / 3.) * nx, sy + ((i) / 3.) * (ey - sy) + ((j) / 3.) * ny, 
          sx + ((i + 1) / 3.) * (ex - sx) + ((j) / 3.) * nx, sy + ((i + 1) / 3.) * (ey - sy) + ((j) / 3.) * ny,
          n - 1, r, g, b, a);
      }
    }
    Sint16 xs[] = {
          sx + (1. / 3.) * (ex - sx) + (1. / 3.) * nx,
          sx + (1. / 3.) * (ex - sx) + (2. / 3.) * nx,
          sx + (2. / 3.) * (ex - sx) + (2. / 3.) * nx,
          sx + (2. / 3.) * (ex - sx) + (1. / 3.) * nx
        };
        Sint16 ys[] = {
          sy + (1. / 3.) * (ey - sy) + (1. / 3.) * ny,
          sy + (1. / 3.) * (ey - sy) + (2. / 3.) * ny,
          sy + (2. / 3.) * (ey - sy) + (2. / 3.) * ny,
          sy + (2. / 3.) * (ey - sy) + (1. / 3.) * ny
        };
  filledPolygonRGBA(ecran, xs, ys, 4, 0.9 * r, 0.9 * g, 0.9 * b, a);
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
    tapis_sierpinski_aux(ecran, sx, sy, ex, ey, n, r, g, b, a);
}

void triangle_sierpinski_aux(SDL_Surface * ecran, double sx, double sy, double ex, double ey, int n, int r, int g, int b, int a) {
    int nx = (ey - sy);
    int ny = -(ex - sx);
    if(n <= 1) {
        return;
    }
    triangle_sierpinski_aux(ecran, sx, sy, 0.5 * (sx + ex), 0.5 * (sy + ey), n - 1, r, g, b, a);
    triangle_sierpinski_aux(ecran, 0.5 * (sx + ex), 0.5 * (sy + ey), ex, ey, n - 1, r, g, b, a);
    triangle_sierpinski_aux(ecran, 
      0.25 * (3 * sx + ex) + 0.87 * 0.5 * nx, 0.25 * (3 * sy + ey) + 0.87 * 0.5 * ny, 
      0.25 * (sx + 3 * ex) + 0.87 * 0.5 * nx, 0.25 * (sy + 3 * ey) + 0.87 * 0.5 * ny, 
      n - 1, r, g, b, a);
    Sint16 xs[] = {
      0.25 * (3 * sx + ex) + 0.87 * 0.5 * nx,
      0.25 * (sx + 3 * ex) + 0.87 * 0.5 * nx,
      0.5 * (sx + ex)
    };
    Sint16 ys[] = {
      0.25 * (3 * sy + ey) + 0.87 * 0.5 * ny,
      0.25 * (sy + 3 * ey) + 0.87 * 0.5 * ny,
      0.5 * (sy + ey)
    };
    filledPolygonRGBA(ecran, xs, ys, 3, r, g, b, a);
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
    triangle_sierpinski_aux(ecran, sx, sy, ex, ey, n, r, g, b, a);
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
    fprintf(stderr, "Еrror in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Surface * ecran = NULL;
  if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    fprintf(stderr, "Еrror in SDL_SetVideoMode : %s\n", SDL_GetError());
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