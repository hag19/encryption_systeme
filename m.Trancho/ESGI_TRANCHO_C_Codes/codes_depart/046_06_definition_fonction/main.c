#include <stdio.h>
#include <stdlib.h>

/* TODO : fonction carre qui prend un int en entrée et renvoie un int en sortie */

int main() {
  int a = 41;
  printf("(%d + 1) * (%d + 1) = %d\n", a, a, 
  (a + 1) * (a + 1));
  printf("carre(%d + 1) = %d\n", a, carre(a + 1));
  if((a + 1) * (a + 1) == carre(a + 1))
    printf("Bravo !\n");
  return 0;
}