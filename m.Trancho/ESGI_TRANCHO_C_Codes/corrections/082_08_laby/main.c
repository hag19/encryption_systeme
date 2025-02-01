/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 82.
 */

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

/* Position de la caméra et échelle de la vue : */
float cx, cy, cz;

int player_x, player_y;
int exit_x, exit_y;

SDL_Surface * ecran = NULL;

char ** grille = NULL;
int grille_largeur = 10;
int grille_hauteur = 10;

double ecran_depuis_camera_x(double x) {
  return ((x - cx) * largeur / 2) / cz + largeur / 2;
}

double ecran_depuis_camera_y(double y) {
  return ((y - cy) * hauteur / 2) / cz + hauteur / 2;
}

double ecran_depuis_camera_z(double z) {
  return (z * largeur / 2.) / cz;
}

double camera_depuis_ecran_x(double x) {
  return 2. * ((x - largeur / 2) * cz) / largeur + cx;
}

double camera_depuis_ecran_y(double y) {
  return 2. * ((y - hauteur / 2) * cz) / hauteur + cy;
}

double camera_depuis_ecran_z(double z) {
  return (2 * z * cz) / largeur;
}

/* Allocation dynamique d'un tableau à deux dimensions : */
void grille_creer(int width, int height) {
  char * data = NULL;
  if(grille) {
    free(*grille);
    free(grille);
    grille = NULL;
  }
  assert((data = (char *)calloc(width * height, sizeof(char))) != NULL);
  assert((grille = (char **)malloc(width * sizeof(char *))) != NULL);
  int i;
  for(i = 0; i < width; ++i) {
    grille[i] = data + (i * height);
  }
  grille_largeur = width;
  grille_hauteur = height;
}

int in_grille(int x, int y) {
  return x >= 0 && y >= 0 && x < grille_largeur && y < grille_hauteur;
}

int in_inner_grille(int x, int y) {
  return x >= 1 && y >= 1 && x < grille_largeur - 1 && y < grille_hauteur - 1;
}

/* Mise en place d'une pile pour dérecursiver la fonction creuser : */
void stack_update(unsigned long long ** stack, int * taille, int * capacite) {
  if(*taille < *capacite) {
    if(*taille * 4 < *capacite) {
      *capacite = *capacite / 2;
    } else {
      return ;
    }
  } else {
    *capacite = *taille * 2 + 10;
  }
  assert((*stack = (unsigned long long *)realloc(*stack, *capacite * sizeof(unsigned long long))) != NULL);
}

void stack_push(unsigned long long value, unsigned long long ** stack, int * taille, int * capacite) {
  stack_update(stack, taille, capacite);
  (*stack)[(*taille)++] = value;
}

int stack_pop(unsigned long long * value, unsigned long long ** stack, int * taille, int * capacite) {
  if(*taille <= 0) return 0;
  stack_update(stack, taille, capacite);
  *value = (*stack)[--(*taille)];
  return 1;
}

/* Conversion des valeurs manipulées par la pile en coordonnées : */
void stack_push_coords(int x, int y, unsigned long long ** stack, int * taille, int * capacite) {
  unsigned long long v = (unsigned long long)x * 0x100000000 + y;
  stack_push(v, stack, taille, capacite);
}

int stack_pop_coords(int * x, int * y, unsigned long long ** stack, int * taille, int * capacite) {
  unsigned long long v;
  if(! stack_pop(&v, stack, taille, capacite)) return 0;
  *x = v / 0x100000000;
  *y = v % 0x100000000;
  return 1;
}

/* Récupère une valeur dans la grille ou une valeur extérieure aléatoire : */
int get_grille(int x, int y) {
  if(in_grille(x, y)) return grille[x][y];
  double v = cos(512 * (y + 0.1 * x + 200) * (0.25 * x + y) * (50 - 0.2 * y + 0.6 * x));
  return (v > 0.) ? '#' : '.';
}

int can_move(int x, int y) {
  return get_grille(x, y) != '#';
}

/* Version dérecursivée de creuser : */
void creuser_stack(unsigned long long ** stack, int * taille, int * capacite) {
  int x, y;
  while(stack_pop_coords(&x, &y, stack, taille, capacite)) {
    if(! in_grille(x, y)) continue ;
    if(grille[x][y] != '#') continue ;
    int link4 = 0;
    int link8 = 0;
    int i, j;
    int dx = 1, dy = 0;
    int tmp;
    for(i = 0; i < 4; ++i) {
      link4 += (get_grille(x + dx, y + dy) == '.');
      tmp = dx;
      dx = dy;
      dy = -tmp;
    }
    
    /* S'il y a déjà deux liens en connectivité 4, on ignore. */
    if(link4 > 1) continue ;
    
    dx = 1; dy = 1;
    for(i = 0; i < 4; ++i) {
      link8 += (get_grille(x + dx, y + dy) == '.');
      tmp = dx;
      dx = dy;
      dy = -tmp;
    }
    link8 += link4;
    
    if(link8 > 2) continue ;
    
    if(grille[x][y] != '#') {
      continue;
    }
    grille[x][y] = '.';
    
    dx = 1; dy = 0;
    j = rand() % 4;
    for(i = 0; i < j; ++i) {
      tmp = dx;
      dx = dy;
      dy = -tmp;
    }
    for(i = 0; i < 4; ++i) {
      if(in_grille(x + dx, y + dy) && grille[x + dx][y + dy] == '#') {
        stack_push_coords(x + dx, y + dy, stack, taille, capacite);
      }
      tmp = dx;
      dx = dy;
      dy = -tmp;
    }
  }
}

void placer_sortie() {
  int x, y;
  double d;
  double maxi = 0;
  int i;
  /* On sélectionne la sortie la plus éloignée du joueur pour un */
  /* nombre de proposition en fonction de la taille de la grille. */
  for(i = 0; i < (grille_largeur + grille_hauteur) / 2; ++i) {
    do {
      x = rand() % grille_largeur;
      y = rand() % grille_hauteur;
    } while(grille[x][y] == '#');
    d = pow(x - player_x, 2.) + pow(y - player_y, 2.);
    if(i == 0 || d > maxi) {
      exit_x = x;
      exit_y = y;
      maxi = d;
    }
  }
}

void grille_generer(int width, int height) {
  grille_creer(width, height);
  int x, y;
  for(x = 0; x < width; ++x) {
    for(y = 0; y < height; ++y) {
      grille[x][y] = '#';
    }
  }
  unsigned long long * stack = NULL;
  int taille = 0;
  int capacite = 0;
  stack_push_coords(player_x, player_y, &stack, &taille, &capacite);
  creuser_stack(&stack, &taille, &capacite);
  placer_sortie();
}

int check_finish() {
  if(! (player_x == exit_x && player_y == exit_y)) return 0;
  /* Si le joueur a atteint la sortie, on génère le niveau suivant : */
  grille_largeur = grille_largeur * 1.1 + 1;
  grille_hauteur = grille_hauteur * 1.1 + 1;
  player_x = grille_largeur / 2;
  player_y = grille_hauteur / 2;
  clock_t start, end;
  start = clock();
  grille_generer(grille_largeur, grille_hauteur);
  end = clock();
  printf("Génération d'une grille %dx%d en %g s\n", grille_largeur, grille_hauteur, (double)(end - start) / CLOCKS_PER_SEC);
  return 1;
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

/* Surcouche de filledPieColor en fonction de la connectivité de la grille : */
void part_filledPieColor(SDL_Surface * ecran, int x, int y, int d, int dx, int dy, int c) {
  int start_angle = 0, end_angle = 0;
  switch(dx + 2 * dy) {
    case 3 : start_angle = 0; end_angle = 90; break;
    case -1 : start_angle = 270; end_angle = 360; break;
    case 1 : start_angle = 90; end_angle = 180; break;
    case -3 : start_angle = 180; end_angle = 270; break;
    default : return ;
  }
  filledPieColor(ecran, x, y, d, start_angle, end_angle, c);
}

/* Fonction de dessin stylisée en fonction de la connectivité : */
void draw_box(int x, int y) {
  int dx = 1, dy = 1;
  int tmp;
  int i;
  int corner, ver, hor;
  for(i = 0; i < 4; ++i) {
    corner = (get_grille(x + dx, y + dy) == '#');
    hor = (get_grille(x + dx, y) == '#');
    ver = (get_grille(x, y + dy) == '#');
    if(hor || ver) {
      if(hor && ver) {
        
        boxColor(ecran, 
          ecran_depuis_camera_x(x), ecran_depuis_camera_y(y), 
          ecran_depuis_camera_x(x + dx * 0.5), ecran_depuis_camera_y(y + dy * 0.5),
          0x11417Aff);
        if(! corner) {
          part_filledPieColor(ecran, 
            ecran_depuis_camera_x(x + dx * 0.5), ecran_depuis_camera_y(y + dy * 0.5), ecran_depuis_camera_z(0.5),
            -dx, -dy,
            0x60839Bff);
        }
      } else {
        boxColor(ecran, 
          ecran_depuis_camera_x(x), ecran_depuis_camera_y(y), 
          ecran_depuis_camera_x(x + dx * 0.5), ecran_depuis_camera_y(y + dy * 0.5),
          0x60839Bff);
      }
    } else {
      part_filledPieColor(ecran, 
        ecran_depuis_camera_x(x), ecran_depuis_camera_y(y), ecran_depuis_camera_z(0.5),
        dx, dy,
        0x60839Bff);
    }
    tmp = dx;
    dx = dy;
    dy = -tmp;
  }
}

void afficher_grille() {
  int x, y;
  int sx, sy, ex, ey;
  int step;
  step = camera_depuis_ecran_z(1);
  if(step < 1) step = 1;
  sx = camera_depuis_ecran_x(0) - 0.5 * step;
  sy = camera_depuis_ecran_y(0) - 0.5 * step;
  ex = camera_depuis_ecran_x(largeur) + 1.5 * step;
  ey = camera_depuis_ecran_y(hauteur) + 1.5 * step;
  /*if(sx < 0) sx = 0;
  if(sy < 0) sy = 0;
  if(ex >= grille_largeur) ex = grille_largeur;
  if(ey >= grille_hauteur) ey = grille_hauteur;*/
  for(x = sx; x < ex; x += step) {
    for(y = sy; y < ey; y += step) {
      switch(get_grille(x, y)) {
#ifdef NO_STYLE
        case '#' : boxColor(ecran, 
          ecran_depuis_camera_x(x - 0.5), ecran_depuis_camera_y(y - 0.5), 
          ecran_depuis_camera_x(x + 0.5), ecran_depuis_camera_y(y + 0.5),
          0x11417Aff); break;
#else
        case '#' : draw_box(x, y); break;
#endif
        default : break;
      }
    }
  }
}

void affichage() {
  /* Remplissage de l'écran par un gris foncé uniforme : */
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0x9E, 0x7D, 0x3C));
  afficher_grille();
  filledCircleColor(ecran, 
    ecran_depuis_camera_x(player_x), ecran_depuis_camera_y(player_y), 
    ecran_depuis_camera_z(0.5),
    0x66CE48ff);
  filledCircleColor(ecran, 
    ecran_depuis_camera_x(exit_x), ecran_depuis_camera_y(exit_y), 
    ecran_depuis_camera_z(0.5),
    0xFDCB22ff);
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
  
  free(*grille);
  free(grille);
  grille = NULL;
  
  SDL_FreeSurface(ecran);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}