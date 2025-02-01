#include <stdio.h>
#include <stdlib.h>

void afficher_tableau(/* TODO : passer un tableau */) {
  /* TODO : afficher les valeurs positives sous la forme : */
  /* [1, 2, 3, 4, 5] */
}

int main() {
  /* TODO : définir un tableau d'entiers avec les valeurs */
  /* suivantes : 1, 2, 3, 4, 5 et -1 */
  int indice;
  int valeur;
  afficher_tableau(tableau);
  printf("Quel indice affecter ? ");
  scanf("%d", &indice);
  printf("Pour quelle valeur ? ");
  scanf("%d", &valeur);
  /* TODO : affecter valeur à l'indice "indice" du tableau */
  afficher_tableau(tableau);
  exit(EXIT_SUCCESS);
}