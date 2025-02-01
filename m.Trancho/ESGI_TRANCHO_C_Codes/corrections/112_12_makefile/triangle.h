/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 87.
 */

#ifndef DEF_HEADER_TRIANGLE
#define DEF_HEADER_TRIANGLE

#include "point.h"

typedef struct Triangle Triangle;
struct Triangle {
  Point first;
  Point second;
  Point third;
};

Triangle Triangle_creer(Point first, Point second, Point third);

void Triangle_afficher(const Triangle * triangle);

double Triangle_perimetre(const Triangle * triangle);

#endif