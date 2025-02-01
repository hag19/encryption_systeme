/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

struct Personnage {
  unsigned int pointsDeVie;
  unsigned int pointsDeVieMax;
  unsigned int niveau;
  unsigned long experience;
  unsigned char aStatutPoison;
  unsigned char aStatutParalyse;
  unsigned char aStatutEndormi;
  unsigned int attaque;
  unsigned int defense;
  unsigned int attaqueSpe;
  unsigned int defenseSpe;
  unsigned int vitesse;
};

struct PersonnageCompress {
  unsigned int pointsDeVie : 10;
  unsigned int pointsDeVieMax : 10;
  unsigned int niveau : 7;
  unsigned long experience : 40;
  unsigned char aStatutPoison : 1;
  unsigned char aStatutParalyse : 1;
  unsigned char aStatutEndormi : 1;
  unsigned int attaque : 10;
  unsigned int defense : 10;
  unsigned int attaqueSpe : 10;
  unsigned int defenseSpe : 10;
  unsigned int vitesse : 10;
};

int main() {
  printf("%lu\n", sizeof(struct Personnage));
  printf("%lu\n", sizeof(struct PersonnageCompress));
  exit(EXIT_SUCCESS);
}