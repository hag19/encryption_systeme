#include <stdio.h>
#include <stdlib.h>

int ** allouer_grille(int largeur, int hauteur);
void afficher(int ** grille, int largeur, int hauteur);
void fill(int ** grille, int largeur, int hauteur);
void free_grille(int *** grille);

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