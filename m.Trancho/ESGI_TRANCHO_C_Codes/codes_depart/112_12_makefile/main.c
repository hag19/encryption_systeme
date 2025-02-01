#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point Point;
struct Point {
  double x;
  double y;
};

Point Point_creer(double x, double y) {
  Point p = {x, y};
  return p;
}

void Point_afficher(const Point * p) {
  printf("(%g, %g)", p->x, p->y);
}

double Point_distance(const Point * first, const Point * second) {
  return sqrt(pow(second->x - first->x, 2) + pow(second->y - first->y, 2));
}

typedef struct Triangle Triangle;
struct Triangle {
  Point first;
  Point second;
  Point third;
};

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