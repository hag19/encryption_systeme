/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

void tic(int);
void tac(int);

void tic(int nombre) {
  if(nombre > 0) {
    printf("> tic !\n");
    tac(nombre - 1);
  }
}

void tac(int nombre) {
  if(nombre > 0) {
    printf("< tac !\n");
    tic(nombre - 1);
  }
}

int main() {
  tic(4);
  exit(EXIT_SUCCESS);
}