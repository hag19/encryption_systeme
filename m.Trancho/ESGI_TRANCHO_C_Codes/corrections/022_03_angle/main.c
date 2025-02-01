/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 22.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  double deg_angle;
  printf("Entrez un angle : ");
  scanf("%lf", &deg_angle);
  /* Conversion de l'angle en radians : */
  double rad_angle = deg_angle * M_PI / 180.;
  /* Appel aux fonctions mathématiques cos et sin : */
  printf("cos(%g°) = %g\n", deg_angle, cos(rad_angle));
  printf("sin(%g°) = %g\n", deg_angle, sin(rad_angle));
  exit(EXIT_SUCCESS);
}