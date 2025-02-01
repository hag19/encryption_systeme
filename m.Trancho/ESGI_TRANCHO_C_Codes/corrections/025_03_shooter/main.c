/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 25.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Utilisation de SDL : */
/* Compilation Linux avec les flags -lm -lSDL -lSDL_gfx */

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 800;
const char * titre = "ESGI single shooter";

/* Coordonnées du joueur : */
int px, py;
/* Ligne de tir du joueur : */
int slpx, slpy;
/* Vitesse du joueur : */
int pv;

/* Coordonnées de l'adversaire : */
int ax, ay;
/* Vitesse de l'adversaire : */
int av;

void joueur_se_dirige_vers(int tx, int ty) {
  /* On calcule le vecteur de déplacement vers la cible. */
  int vx = tx - px;
  int vy = ty - py;
  /* On calcule la norme de ce vecteur et ignore le      */
  /* déplacement si trop petit : évite division par 0 .  */
  int v = sqrt(vx * vx + vy * vy);
  if(v < 1) {
    return ;
  } else if(v < pv) {
    /* Cas où le déplacement est plus petit que la     */
    /* vitesse : permet plus de précision au joueur.   */
    px += vx;
    py += vy;
    return;
  }
  /* On déplace le joueur d'un pas de sa vitesse.        */
  px += (pv * vx) / v;
  py += (pv * vy) / v;
}

void adversaire_se_dirige_vers(int tx, int ty) {
  /* Déplacement de l'adversaire analogue à celui de     */
  /* joueur (Voir joueur_se_dirige_vers).                */
  int vx = tx - ax;
  int vy = ty - ay;
  int v = sqrt(vx * vx + vy * vy);
  if(v < 1) {
    return ;
  } else if(v < av) {
    ax += vx;
    ay += vy;
    return;
  }
  ax += (av * vx) / v;
  ay += (av * vy) / v;
}

void joueur_regarde(int tx, int ty) {
  /* On calcule le vecteur de direction vers la cible.   */
  int vx = tx - px;
  int vy = ty - py;
  int v = sqrt(vx * vx + vy * vy);
  /* Si la souris est sur le joueur, on place la fin de  */
  /* la ligne sur la position du joueur : non visible.   */
  if(v < 1) {
    slpx = px;
    slpy = py;
    return ;
  }
  /* On envoie la position de fin de la ligne hors de la */
  /* fenêtre (changement d'échelle du vecteur directeur).*/
  int dv = largeur + hauteur;
  slpx = px + (dv * vx) / v;
  slpy = py + (dv * vy) / v;
}

int distance_tir(int x, int y) {
  /* On prend la direction de la ligne de tir.           */
  int vx = slpx - px;
  int vy = slpy - py;
  int v = sqrt(vx * vx + vy * vy);
  /* Si l'adversaire n'est pas devant le joueur ou collé */
  /* nous renvoyons une distance invalide : trop loin.   */
  if((x - px) * vx + (y - py) * vy < 0
  || v < 1) {
    return 0x7fffffff;
  }
  /* Le produit scalaire à un vecteur normalisé donne la */
  /* distance signée à la droite auquel ce vecteur est   */
  /* perpendiculaire : nous le faisons tourner d'un      */
  /* angle droit pour réaliser ce produit scalaire :     */
  /* (a, b) -> (b, -a).                                  */
  return abs(vy * (x - px) - vx * (y - py)) / v;
}

void place_adversaire() {
  /* On prend un angle aléatoire pour placer             */
  /* l'adversaire hors de la fenêtre.                    */
  int angle = rand() % 360;
  /* Les distances verticales et horizontales sont de    */
  /* l'ordre de (largeur + hauteur) / 4. D'après le      */
  /* théorème de Pythagore, la distance du centre à un   */
  /* serait de l'ordre de                                */
  /* sqrt(2) * distance(centre, côté)                    */
  /* = sqrt(2) * (largeur + hauteur) / 4                 */
  /* = 0.35 * (largeur + hauteur).                       */
  int dv = 0.35 * (largeur + hauteur);
  /* Note : nous avons la position en coordonnées        */
  /* polaires (relativement au centre de la fenêtre) et  */
  /* cos et sin prennent une valeur en radian (d'où la   */
  /* conversion en radian donnée par (produit en croix)  */
  /* (angle * 3.1415) / 180 .                            */
  ax = dv * cos((angle * 3.1415) / 180) + largeur / 2;
  ay = dv * sin((angle * 3.1415) / 180) + hauteur / 2;
}

int distance_joueur(int x, int y) {
  /* Mesure de la distance entre la position du joueur   */
  /* et la position donnée (norme d'un vecteur /         */
  /* théorème de Pythagore).                             */
  int vx = x - px;
  int vy = y - py;
  return sqrt(vx * vx + vy * vy);
}

void affichage(SDL_Surface * ecran) {
  /* Remplissage de l'écran par un gris foncé uniforme : */
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
  /* Affichage du joueur : */
  filledCircleRGBA(ecran, px, py, 25, 51, 204, 51, 255);
  /* Affichage de l'adversaire : */
  filledCircleRGBA(ecran, ax, ay, 25, 204, 51, 51, 255);
  
  lineRGBA(ecran, px, py, slpx, slpy, 102, 255, 102, 255);
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
  px = ecran->w / 2;
  py = ecran->h / 2;
  pv = 10;
  
  ax = ecran->w / 2;
  ay = 0;
  av = 5;
  
  int active = 1;
  int grab = 0;
  SDL_Event event;
  int last_mouse_x = px;
  int last_mouse_y = py;
  
  int score = 0;
  char display[100];
                                   
  while(active) {
    
    affichage(ecran);
    sprintf(display, "Score : %d", score);
    stringRGBA(ecran, 5, 5, display, 255, 255, 255, 255);
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
        
        /* Utilisateur commence le clic : */
        case SDL_MOUSEBUTTONDOWN : {
          switch(event.button.button) {
            case SDL_BUTTON_LEFT : {
              grab = 1;
              last_mouse_x = event.button.x;
              last_mouse_y = event.button.y;
            } break;
            
            case SDL_BUTTON_RIGHT : {
              if(abs(distance_tir(ax, ay)) < 25) {
                ++score;
                ++pv;
                ++av;
                place_adversaire();
              }
            } break;
          }
        } break;
        
        /* Utilisateur relâche le clic : */
        case SDL_MOUSEBUTTONUP : {
          switch(event.button.button) {
            case SDL_BUTTON_LEFT : {
              grab = 0;
            } break;
          }
        } break;
        
        /* Utilisateur bouge la souris : */
        case SDL_MOUSEMOTION : {
          last_mouse_x = event.motion.x;
          last_mouse_y = event.motion.y;
        } break;
      }
    }
    if(grab) {
      joueur_se_dirige_vers(last_mouse_x, last_mouse_y);
    }
    joueur_regarde(last_mouse_x, last_mouse_y);
    adversaire_se_dirige_vers(px, py);
    if(distance_joueur(ax, ay) < 25) {
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 204, 51, 51));
      filledCircleRGBA(ecran, px, py, 25, 0, 0, 0, 255);
    stringRGBA(ecran, 5, 5, display, 255, 255, 255, 255);
      SDL_Flip(ecran);
      SDL_Delay(1000);
      active = 0;
    }
    SDL_Delay(1000 / 60);
  }
                                  
  SDL_FreeSurface(ecran);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}