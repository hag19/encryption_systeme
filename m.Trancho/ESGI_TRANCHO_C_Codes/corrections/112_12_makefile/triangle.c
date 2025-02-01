/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 87.
 */

#include "triangle.h"

#include <stdio.h>

Triangle Triangle_creer(Point first, Point second, Point third) {
  Triangle triangle = {first, second, third};
  return triangle;
}

void Triangle_afficher(const Triangle * triangle) {
  printf("{Triangle : ");
  Point_afficher(&(triangle->first));
  printf(", ");
  Point_afficher(&(triangle->second));
  printf(", ");
  Point_afficher(&(triangle->third));
  printf("}");
}

double Triangle_perimetre(const Triangle * triangle) {
  return
    Point_distance(&(triangle->first), &(triangle->second))
    + Point_distance(&(triangle->second), &(triangle->third))
    + Point_distance(&(triangle->third), &(triangle->first));
}