#include <stdio.h>
#include <stdlib.h>

typedef unsigned long Bit8x8Grid;

Bit8x8Grid Bit8x8Grid_creer();

int Bit8x8Grid_getoffset(int x, int y);

void Bit8x8Grid_afficher(FILE * flow, Bit8x8Grid grille);

void Bit8x8Grid_set(Bit8x8Grid * grille, int x, int y, unsigned char valeur);

unsigned char Bit8x8Grid_get(Bit8x8Grid grille, int x, int y);

int main() {
  Bit8x8Grid grille = Bit8x8Grid_creer();
  Bit8x8Grid_set(&grille, 3, 1, 1);
  Bit8x8Grid_set(&grille, 7, 7, 1);
  Bit8x8Grid_afficher(stdout, grille);
  exit(EXIT_SUCCESS);
}