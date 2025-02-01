/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 93.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/* clear_grille efface tous les symboles de la grille en les   */
/* mettant à ' '                                               */
void clear_grille(char grille[3][3]) {
  int i;
  /* Parcours des 9 éléments de la grille. */
  for(i = 0; i < 9; ++i) {
    /* Astuce : cet indice peut donner ligne par i / 3 et      */
    /* colonnes par i % 3.                                     */
    grille[i / 3][i % 3] = ' ';
  }
}

int finish_grille(char grille[3][3]) {
  /* v modélisera le vainqueur si trouvé. */
  char v = ' ';
  int i;
  int j;
  for(i = 0; i < 3; ++i) {
    /* Parcours sur les lignes : on regarde si sur une même    */
    /* ligne nous avons qu'un élément et son successeur sont   */
    /* égaux deux.                                             */
    if(grille[i][0] == grille[i][1] 
    && grille[i][1] == grille[i][2]) {
      /* Si c'est le cas, nous mettons la valeur à laquelle    */
      /* ils sont tous égaux dans v pour désigner un           */
      /* vainqueur.                                            */
      v = grille[i][0];
      break;
    }
    /* Parcours sur les colonnes : similairement à celui sur   */
    /* les lignes.                                             */
    if(grille[0][i] == grille[1][i] 
    && grille[1][i] == grille[2][i]) {
      v = grille[0][i];
      break;
    }
  }
  /* Vérification diagonales : */
  if(grille[0][0] == grille[1][1] 
  && grille[1][1] == grille[2][2]) {
    v = grille[0][0];
  }
  if(grille[2][0] == grille[1][1] 
  && grille[1][1] == grille[0][2]) {
    v = grille[2][0];
  }
  /* Selon la valeur de v nous avons un vainqueur ou non. */
  /* Si le joueur 1 'X' gagne nous revoyons 1. */
  /* Si le joueur 2 'O' gagne nous revoyons -1. */
  /* Sinon 0 si pas de vainqueur. */
  if(v == 'X') {
    return 1;
  }
  if(v == 'O') {
    return -1;
  }
  return 0;
}

void afficher_grille(char grille[3][3]) {
  int i;
  int j;
  /* Itère sur les lignes pour afficher la grille */
  for(i = 0; i < 4; ++i) {
    mvprintw(2 * i, 0, "+-+-+-+");
    if(i == 3)
      break;
    mvprintw(2 * i + 1, 0, "|%c|%c|%c|", grille[i][0], 
      grille[i][1], grille[i][2]);
  }
}

/* placer_grille permet de placer le joueur 1 'X' (valeur 1)   */
/* ou le joueur 2 'O' (valeur -1) dans la grille si la coup    */
/* est valide.                                                 */
int placer_grille(char grille[3][3], int ligne, int colonne, 
    int joueur) {
  /* La case n'est pas vide : coup invalide. */
  if(grille[ligne][colonne] != ' ') {
    return 0;
  }
  /* joueur 1 'X' (valeur 1) place son pion 'X' */
  if(joueur == 1) {
    grille[ligne][colonne] = 'X';
    return 1;
  }
  /* joueur 2 'O' (valeur -1) place son pion 'O' */
  if(joueur == -1) {
    grille[ligne][colonne] = 'O';
    return 1;
  }
  return 0;
}

int main() {
  /* grille de taille 3 x 3. */
  char grille[3][3];
  /* désignation d'un vainqueur. */
  int win;
  /* joueur auquel c'est le tour (1 pour le premier et -1 pour */
  /* le second).                                               */
  int joueur = 1;
  /* position du coup ) jouer. */
  int place;
  /* nombre de coups déjà joués. */
  int coups;
  /* Fonctions d'initilisation d'une fenêtre ncurses. */
  initscr();
  noecho();
  cbreak();
  
  clear_grille(grille);
  
  for(coups = 0; coups < 9; ++coups) {
    /* Affichage de la grille : */
    clear();
    afficher_grille(grille);
    refresh();
    /* Récupération d'une caractère via ncurses. */
    place = getch();
    /* Une position valide est entre 1 et 9 (pavé numérique). */
    if(place < '1' || place > '9') {
      /* Si invalide on relance la boucle : pas de traitement. */
      --coups;
      continue;
    }
    /* On peut passer d'une représentation {'1' à '9'} à       */
    /* {(ligne, colonne)}.                                     */
    /* Pour indices de 0 à 8 (application du - '1' pour les    */
    /* obtenir).                                               */
    place -= '1';
    /* On obtient la ligne par place / 3. (2 - permet de       */
    /* reverser le sens en ordonnée)                           */
    /* 0, 1, 2 donnent 0; 3, 4, 5 donnent 1; 6, 7, 8 donnent 2 */
    /* Et la colonne par place % 3.                            */
    /* 0, 3, 6 donnent 0; 1, 4, 7 donnent 1; 2, 5, 8 donnent 2 */
    if(! placer_grille(grille, 2 - place / 3, 
                       place % 3, joueur)) {
      /* Si invalide on relance la boucle. */
      --coups;
      continue;
    }
    /* Coup valide : on change le tour du joueur devant jouer. */
    joueur *= -1;
    /* Renvoie un vainqueur (1 ou -1 : valeur de vérité pour   */
    /* vrai) sinon 0 (faux)                                    */
    if(win = finish_grille(grille)) {
      break;
    }
  }
  /* Affiche le gagnant : */
  clear();
  afficher_grille(grille);
  if(win == 0) {
    mvprintw(1, 10, "Pas de gagnant");
  } else {
    mvprintw(1, 10, "Le joueur %c gagne !", 
      (win == 1) ? 'X' : 'O');
  }
  refresh();
  getch();
  
  /* Termine ncurses proprement : */
  refresh();
  clrtoeol();
  refresh();
  endwin();
  exit(EXIT_SUCCESS);
}