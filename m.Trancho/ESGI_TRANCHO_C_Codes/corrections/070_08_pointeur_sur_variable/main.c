/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 70.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int ma_maison = 42;
  int nouvelle_maison = 0;
  int * mon_adresse = &ma_maison;
  int * nouvelle_adresse = &nouvelle_maison;
  printf("[%c] Je sais où est ma maison ?\n", 
    (mon_adresse == &ma_maison) ? 'V' : 'X');
  printf("[%c] Je sais où déménager ?\n", 
    (nouvelle_adresse == &nouvelle_maison) ? 'V' : 'X');
  *nouvelle_adresse = *mon_adresse;
  *mon_adresse = 0;
  printf("[%c] J'ai tout déménagé dans ma nouvelle maison ?\n", 
    (ma_maison == 0) ? 'V' : 'X');
  printf("[%c] J'ai oublié des choses dans ma maison ?\n", 
    (nouvelle_maison == 42) ? 'V' : 'X');
  mon_adresse = nouvelle_adresse;
  (*mon_adresse)++;
  printf("[%c] J'habite à ma nouvelle adresse ?\n", 
    (mon_adresse == &nouvelle_maison) ? 'V' : 'X');
  printf("[%c] J'ai ajouté des choses dans ma maison ?\n", 
    (nouvelle_maison == 43) ? 'V' : 'X');
  exit(EXIT_SUCCESS);
}