/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 32.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  double a, b, c;
  printf("Soit ax^2 + bx + c une expression polynômiale,\nEntrez les coefficients a, b et c :\n");
  scanf("%lf %lf %lf", &a, &b, &c);
  
  printf("Pour le polynôme P : x -> %lg.x^2 + %lg.x + %lg :\n", a, b, c);
  
  if(a != 0) {
    double delta = b * b - 4 * a * c;
    
    if(delta < 0) {
      printf("Il n'y a pas de racine réelle.\n");
      
    } else if(delta > 0) {
      double x1 = (-b - sqrt(delta)) / (2 * a);
      double x2 = (-b + sqrt(delta)) / (2 * a);
      
      printf("Il y a deux racines réelles : %lg et %lg\n", x1, x2);
      printf("P(x) = %lg.x^2 + %lg.x + %lg = %lg.(x - %lg).(x - %lg)\n", a, b, c, a, x1, x2);
      printf("P(%lg) = %lg\n", x1, a * x1 * x1 + b * x1 + c);
      printf("P(%lg) = %lg\n", x2, a * x2 * x2 + b * x2 + c);
      
    } else {
      double x0 = -b / (2 * a);
      
      printf("Il y a une racine réelle : %lg\n", x0);
      printf("P(x) = %lg.x^2 + %lg.x + %lg = %lg.(x - %lg)^2\n", a, b, c, a, x0);
      printf("P(%lg) = %lg\n", x0, a * x0 * x0 + b * x0 + c);
    }
  } else if(b != 0) {
    double x0 = -c / b;
    
    printf("Il y a une racine réelle : %lg\n", x0);
    printf("P(x) = %lg.x^2 + %lg.x + %lg = %lg.(x - %lg)\n", a, b, c, b, x0);
    printf("P(%lg) = %lg\n", x0, a * x0 * x0 + b * x0 + c);
    
  } else {
    printf("P est une fonction constante égale à %lg\n", c);
  }
  exit(EXIT_SUCCESS);
}