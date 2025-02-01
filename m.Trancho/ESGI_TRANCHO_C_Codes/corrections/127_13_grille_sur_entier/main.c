/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 127.
 */

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

Bit8x8Grid Bit8x8Grid_creer() {
  return (Bit8x8Grid)0;
}

int Bit8x8Grid_getoffset(int x, int y) {
  return x + 8 * y;
}

void Bit8x8Grid_afficher(FILE * flow, Bit8x8Grid grille) {
  int x, y;
  for(y = 0; y < 8; ++y) {
    for(x = 0; x < 8; ++x) {
      fputc(Bit8x8Grid_get(grille, x, y) ? '#' : '~', flow);
    }
    fputc('\n', flow);
  }
}

void Bit8x8Grid_set(Bit8x8Grid * grille, int x, int y, unsigned char valeur) {
  int offset = Bit8x8Grid_getoffset(x, y);
  valeur = !!valeur;
  *grille &= ~((Bit8x8Grid)1 << offset);
  *grille |= (Bit8x8Grid)valeur << offset;
}

unsigned char Bit8x8Grid_get(Bit8x8Grid grille, int x, int y) {
  int offset = Bit8x8Grid_getoffset(x, y);
  return !!(grille & ((Bit8x8Grid)1 << offset));
}