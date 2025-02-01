/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 117.
 */

#ifndef DEF_HEADER_POINT
#define DEF_HEADER_POINT

typedef struct Point Point;
struct Point {
  double x;
  double y;
};

Point Point_creer(double x, double y);

void Point_afficher(const Point * p);

double Point_distance(const Point * first, const Point * second);

#endif