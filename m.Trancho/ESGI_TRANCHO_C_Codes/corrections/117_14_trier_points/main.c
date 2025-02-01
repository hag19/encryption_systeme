/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 117.
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "point.h"

double Point_distanceCarre_origine(const Point * point) {
  return point->x * point->x + point->y * point->y;
}

int Point_cmpDistanceOrigine(const Point * first, const Point * second) {
  double diff = Point_distanceCarre_origine(first) - Point_distanceCarre_origine(second);
  if(-1.e-9 < diff && diff < 1.e-9) {
    return 0;
  }
  return (diff < 0) ? - 1 : 1;
}

int Point_cmpDistanceTarget(const Point * first, const Point * second, Point * target) {
  double diff = Point_distance(first, target) - Point_distance(second, target);
  if(-1.e-9 < diff && diff < 1.e-9) {
    return 0;
  }
  return (diff < 0) ? (diff - 1) : (diff + 1);
}

int main() {
  Point points[5] = {
    Point_creer(-3, 0),
    Point_creer(4, 0),
    Point_creer(0, 3),
    Point_creer(0, 1),
    Point_creer(2, 3)
  };
  qsort(points, 5, sizeof(Point), 
    (int (*)(const void *, const void *))&Point_cmpDistanceOrigine);
  int i;
  printf("Distance origine : \n");
  for(i = 0; i < 5; ++i) {
    Point_afficher(points + i);
    printf(" %g\n", sqrt(Point_distanceCarre_origine(points + i)));
  }
  Point target = Point_creer(3, 3);
  qsort_r(points, 5, sizeof(Point), 
    (int (*)(const void *, const void *, void *))&Point_cmpDistanceTarget, &target);
  printf("Distance ");
  Point_afficher(&target);
  printf(" : \n");
  for(i = 0; i < 5; ++i) {
    Point_afficher(points + i);
    printf(" %g\n", Point_distance(points + i, &target));
  }
  exit(EXIT_SUCCESS);
}