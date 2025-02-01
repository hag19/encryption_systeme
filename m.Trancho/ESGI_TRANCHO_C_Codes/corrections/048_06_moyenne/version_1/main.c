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

/* Version boucle forever : */
/* définition de la fonction moyenne : */
float moyenne() {
  /* variables locales à la fonction moyenne : */
  float val;
  int nb = 0;
  float sum = 0;
  /* traite les valeurs lues au clavier */
  for(;;) {
    scanf("%f", &val);
    /* sauf si on trouve une valeur négative */
    if(val < 0) {
      break;
    }
    /* la valeur est comptabilisée et ajoutée à la somme */
    sum += val;
    ++nb;
  }
  if(nb > 0) {
    sum /= nb;
  }
  return sum;
}