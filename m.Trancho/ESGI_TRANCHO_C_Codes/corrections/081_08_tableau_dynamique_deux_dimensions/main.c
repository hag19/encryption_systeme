/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 81.
 */

#include <stdio.h>
#include <stdlib.h>

int ** allouer_grille(int largeur, int hauteur) {
  int ** grille = NULL;
  int * data = NULL;
  
  /* Allocation d'une plage mémoire pour la première dimension */
  /* (adresses) et Allocation de la plage mémoire des valeurs  */
  if((grille = (int **)malloc(largeur * sizeof(int *))) == NULL
  || (data = (int *)calloc(largeur * hauteur, sizeof(int))) == NULL) {
    printf("Erreur d'allocation.\n");
    exit(EXIT_FAILURE);
  }
  
  int i;
  /* Les adresses de la première dimension pointent sur un     */
  /* emplacement de la plage mémoire des valeurs.              */
  /* Cette proposition permet de n'avoir que deux allocation   */
  /* au lieu de (largeur + 1) allocations et conserver         */
  /* l'utilisation en tableau à deux dimensions.               */
  for(i = 0; i < largeur; ++i) {
    grille[i] = data + i * hauteur;
  }
  
  return grille;
}

void afficher(int ** grille, int largeur, int hauteur) {
  int x, y;
  for(y = 0; y < hauteur; ++y) {
    for(x = 0; x < largeur; ++x) {
      printf("%c", grille[x][y] ? '#' : '-');
    }
    printf("\n");
  }
}

void fill(int ** grille, int largeur, int hauteur) {
  int i;
  int m = (largeur < hauteur) ? largeur : hauteur;
  /* Remplissage des diagonales carrés : */
  for(i = 0; i < (m + 1) / 2; ++i) {
    grille[i][i] = 1;
    grille[i][hauteur - i - 1] = 1;
    grille[largeur - i - 1][i] = 1;
    grille[largeur - i - 1][hauteur - i - 1] = 1;
  }
  int u = (largeur > hauteur) ? largeur : hauteur;
  /* finition de la jointure entre les diagonales carrés : */
  for(i = 0; i < u - m; ++i) {
    grille[m / 2 + i * (largeur / u)][m / 2 + i * (hauteur / u)] 
      = 1;
  }
}

void free_grille(int *** grille) {
  /* Libération de la plage de valeurs : */
  free(**grille);
  /* Libération de la plage d'adresses : */
  free(*grille);
  /* Perte du lien vers l'adresse de données libérées : */
  *grille = NULL;
}

int main() {
  int largeur, hauteur;
  int ** grille = NULL;
  
  printf("Entrez largeur et hauteur de la grille : ");
  scanf("%d %d", &largeur, &hauteur);
  
  grille = allouer_grille(largeur, hauteur);
  fill(grille, largeur, hauteur);
  afficher(grille, largeur, hauteur);
  free_grille(&grille);
  exit(EXIT_SUCCESS);
}