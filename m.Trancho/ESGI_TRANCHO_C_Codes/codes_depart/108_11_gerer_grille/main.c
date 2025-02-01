#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct Grille Grille;
struct Grille {
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