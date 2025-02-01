/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 87.
 */

#include <stdio.h>
#include <stdlib.h>

#include "triangle.h"

int main() {
  Triangle triangle = Triangle_creer(
    Point_creer(0, 0),
    Point_creer(4, 0),
    Point_creer(0, 3)
  );
  Triangle_afficher(&triangle);
  printf("\nPerimetre : %g\n", Triangle_perimetre(&triangle));
  exit(EXIT_SUCCESS);
}