#include <stdio.h>
#include <stdlib.h>

int main() {
  int valeur = 42;
  int * ptr = ...; /* TODO : pointe sur valeur */
  int ** pptr = ...; /* TODO : pointe sur ptr */
  int *** ppptr = ...; /* TODO : pointe sur pptr */
  printf("valeur via valeur : %d\n", valeur);
  printf("valeur via ptr : %d\n", ...);
  printf("valeur via pptr : %d\n", ...);
  printf("valeur via ppptr : %d\n", ...);
  exit(EXIT_SUCCESS);
}