/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 48.
 */

#include <stdio.h>
#include <stdlib.h>

/* déclaration de la fonction moyenne : */
float moyenne();

int main() {
  printf("La moyenne de ");
  /* appel de la fonction moyenne : */
  printf("= %g\n", moyenne());
  exit(EXIT_SUCCESS);
}

/* Version boucle do-while : */
/* Défaut : nécessite de dupliquer la condition d'arrêt. */
float moyenne() {
  float val;
  int nb = 0;
  float sum = 0;
  /* Boucle infinie : */
  do {
    /* Lecture des entrées : */
    scanf("%f", &val);
    /* Condition d'arrêt dupliquée */
    if(val >= 0) {
      /* Traitement des entrées : */
      sum += val;
      ++nb;
    }
  } while(val >= 0);
  /* Traitement final des données : */
  if(nb > 0) {
    sum /= nb;
  }
  return sum;
}