/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 107.
 */

#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265359
#include <math.h>

/* Nous utilisons un typedef pour s'éviter l'écriture struct   */
/* Vecteur2d dans la suite et la remplacer par une écriture    */
/* Vecteur2d.                                                  */
typedef struct Vecteur2d Vecteur2d;
/* Nous fabriquons une structure avec deux champs : */
struct Vecteur2d {
  double x; /* un champ x réel */
  double y; /* un champ y réel */
};

/* Fonction d'initialisation d'un Vecteur2d depuis des         */
/* coordonnées x et y.                                         */
Vecteur2d Vecteur2d_create(double x, double y) {
  /* Cette syntaxe peut être utilisée à la définition d'une    */
  /* structure comme pour un tableau.                          */
  Vecteur2d p = {x, y};
  /* Nous renvoyons une copie de la structure créée. */
  return p;
}

/* Compatible avec Vecteur2d_create.                           */
/* Les structures sont ici passées par copie et donc ceci ne   */
/* modifiera pas la structure envoyée.                         */
Vecteur2d Vecteur2d_translation(Vecteur2d target, Vecteur2d translation) {
  target.x += translation.x;
  target.y += translation.y;
  /* d'où le besoin de la renvoyer pour affectation : */
  return target;
}

Vecteur2d Vecteur2d_scale(Vecteur2d target, Vecteur2d origin, double scale) {
  target.x = scale * (target.x - origin.x) + origin.x;
  target.y = scale * (target.y - origin.y) + origin.y;
  return target;
}

Vecteur2d Vecteur2d_rotation(Vecteur2d target, Vecteur2d origin, double angleDegree) {
  Vecteur2d res;
  double angle = (angleDegree * M_PI) / 180;
  res.x = cos(angle) * (target.x - origin.x) - sin(angle) * (target.y - origin.y) + origin.x;
  res.y = sin(angle) * (target.x - origin.x) + cos(angle) * (target.y - origin.y) + origin.y;
  return res;
}

void Vecteur2d_print(Vecteur2d vec) {
  printf("(%g, %g)\n", vec.x, vec.y);
}

int main() {
  Vecteur2d p = Vecteur2d_create(0, 0);
  printf("Vecteur2d : ");
  Vecteur2d_print(p);
  p = Vecteur2d_translation(p, Vecteur2d_create(1, 2));
  printf("Translation par un Vecteur2d : ");
  Vecteur2d_print(Vecteur2d_create(1, 2));
  Vecteur2d_print(p);
  p = Vecteur2d_scale(p, Vecteur2d_create(1, 0), 0.5);
  printf("Agrandissement de rapport %g et de centre un Vecteur2d : ", 0.5);
  Vecteur2d_print(Vecteur2d_create(1, 0));
  Vecteur2d_print(p);
  p = Vecteur2d_rotation(p, Vecteur2d_create(0, 2), 135);
  printf("Rotation d'angle %d deg et de centre un Vecteur2d : ", 135);
  Vecteur2d_print(Vecteur2d_create(0, 2));
  Vecteur2d_print(p);
  exit(EXIT_SUCCESS);
}