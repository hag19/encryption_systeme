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

/* Version boucle while : */
/* Défaut: nécessite une première entrée valide */
/* (ceci duplique le code de saisie). */
float moyenne() {
  float val;
  int nb = 0;
  float sum = 0;
  /* Lecture d'une première entrée : */
  scanf("%f", &val);
  /* Boucle tant que : */
  /* Se lance et continue tant qu'une entrée valide est reçue. */
  while(val >= 0) {
    /* Traitement des entrées : */
    sum += val;
    ++nb;
    /* Lecture des entrées suivantes : */
    scanf("%f", &val);
  }
  /* Traitement final des données : */
  if(nb > 0) {
    sum /= nb;
  }
  return sum;
}