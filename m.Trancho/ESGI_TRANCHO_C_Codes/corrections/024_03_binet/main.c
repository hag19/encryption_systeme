/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 24.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Note : l'utilisation de math.h demande l'ajout de -lm */
/* dans la commande de compilation.                      */

/* Le calcul de F_90 donne la valeur 2880067194370816120 */
/* (Ceci est la valeur exacte et attendue)               */
/* Le calcul de F_20000 donne une valeur à 4180 chiffres */
/* Cette approximation est à un facteur environ 3.25e-17 */
/* De la valeur exacte calculée : soit une approximation */
/* pertinente obtenue en environ 3.3e-05 secondes.       */

int main() {
  int n;
  printf("Entrez n : ");
  scanf("%d", &n);
  /* Nous utilisons les mesures de temps clock_t pour */
  /* prouver l'efficacité du calcul.                  */
  clock_t start;
  clock_t end;
  start = clock();
  /* Pour réussir à effectuer les calculs sur un long */
  /* double : nous utilisons les fonctions sqrtl et   */
  /* powl de la bibliothèque math.                    */
  long double first = (1. + sqrtl(5.)) / 2.;
  long double second = (1. - sqrtl(5.)) / 2.;
  long double res = (powl(first, n) - powl(second, n)) / sqrtl(5.);
  end = clock();
  /* Le réglage de 0 chiffres après la virgule permet */
  /* d'obtenir une approximation par un entier et le  */
  /* choix du %f de ne pas avoir d'approximation      */
  /* scientifique. */
  printf("%.0Lf\n", res);
  printf("In %g\n", (double)(end - start) / CLOCKS_PER_SEC);
  exit(EXIT_SUCCESS);
}