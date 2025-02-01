/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 108.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct Grille Grille;
struct Grille {
  /* Notre grille sera modélisée en interne par un tableau à   */
  /* une dimension :                                           */
  char * grille;
  int largeur;
  int hauteur;
};

/* donne un pointeur sur une case de la grille */
char * Grille_case(const Grille * grille, int x, int y);

/* crée une grille de taille donnée */
Grille Grille_creer(int largeur, int hauteur);

/* affiche une grille à l'écran */
void Grille_afficher(const Grille * grille);

/* libère une grille */
void Grille_free(Grille * grille);

int main() {
    int largeur = 60, hauteur = 20;
    Grille grille = Grille_creer(largeur, hauteur);
    int x = 1, y = 1;
    initscr();
    noecho();
    cbreak();
    do {
        clear();
        Grille_afficher(&grille);
        mvprintw(y, x, "@");
        mvprintw(y, x, "");
        refresh();
        getch();
        /* gestion des événements */
    } while(1);
    refresh();
    clrtoeol();
    refresh();
    endwin();
    Grille_free(&grille);
    exit(EXIT_SUCCESS);
}

/* Pour modifier la grille, nous proposons d'obtenir un        */
/* pointeur vers un élément de la grille depuis les            */
/* coordonnées (x, y) de la case de celle-ci. Ceci nous permet */
/* de rester indépendant de la représentation de la grille en  */
/* mémoire (1D, 2D, ...)                                       */
char * Grille_case(const Grille * grille, int x, int y) {
  if(grille == NULL || x < 0 || y < 0 || x >= grille->largeur || y >= grille->hauteur) {
    return NULL;
  }
  return grille->grille + (x + y * grille->largeur);
}

Grille Grille_creer(int largeur, int hauteur) {
  Grille grille = {NULL, 0, 0};
  if((grille.grille = (char *)malloc(sizeof(char) * largeur * hauteur)) == NULL) {
    printf("Allocation de la grille impossible.\n");
    exit(EXIT_FAILURE);
  }
  grille.largeur = largeur;
  grille.hauteur = hauteur;
  int x, y;
  for(x = 0; x < largeur * hauteur; ++x) {
    grille.grille[x] = ' ';
  }
  for(y = 0; y < hauteur; ++y) {
    *Grille_case(&grille, 0, y) = '#';
    *Grille_case(&grille, largeur - 1, y) = '#';
  }
  for(x = 1; x < largeur - 1; ++x) {
    *Grille_case(&grille, x, 0) = '#';
    *Grille_case(&grille, x, hauteur - 1) = '#';
  }
  return grille;
}

void Grille_afficher(const Grille * grille) {
  int x, y;
  for(y = 0; y < grille->hauteur; ++y) {
    for(x = 0; x < grille->largeur; ++x) {
      mvprintw(y, x, "%c", *Grille_case(grille, x, y));
    }
  }
}

void Grille_free(Grille * grille) {
  if(grille == NULL) {
    return;
  }
  free(grille->grille);
  grille->grille = NULL;
  grille->largeur = 0;
  grille->hauteur = 0;
}