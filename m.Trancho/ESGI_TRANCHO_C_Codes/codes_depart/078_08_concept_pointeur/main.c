#include <stdio.h>
#include <stdlib.h>

#define NB_MAISONS 7

void afficher_maison(int * maison);
void afficher_maisons(int * maisons, int nombre);
int * adresse_maison(int * maisons, int numero);
int vider_maison(int * maison);
void vider_camion(int * camion, int * maison);

int main() {
  int * demenageur = NULL;
  int camion = 0;
  int maisons[NB_MAISONS];
  int i;
  
  for(i = 0; i < NB_MAISONS; ++i) {
    maisons[i] = i + 1;
  }
  afficher_maisons(maisons, NB_MAISONS);
  
  printf("camion -> %d\n", camion);
  
  demenageur = adresse_maison(maisons, 3);
  afficher_maison(demenageur);
  camion = vider_maison(demenageur);
  afficher_maison(demenageur);
  
  printf("camion -> %d\n", camion);
  
  demenageur = adresse_maison(maisons, 5);
  afficher_maison(demenageur);
  vider_camion(&camion, demenageur);
  afficher_maison(demenageur);
  
  printf("camion -> %d\n", camion);
  afficher_maisons(maisons, NB_MAISONS);
  
  exit(EXIT_SUCCESS);
}