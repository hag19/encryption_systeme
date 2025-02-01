/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 78.
 */

#include <stdio.h>
#include <stdlib.h>

#define NB_MAISONS 7

void afficher_maison(int * maison) {
  /* Affiche l'adresse pointée par maison et le contenu        */
  /* référencé                                                 */
  printf("%p -> %d\n", maison, *maison);
}

void afficher_maisons(int * maisons, int nombre) {
  int i;
  for(i = 0; i < nombre; ++i) {
    printf("[%d] : ", i);
    afficher_maison(maisons + i);
  }
}

int * adresse_maison(int * maisons, int numero) {
  /* Utilise l'arithématique des pointeurs pour obtenir        */
  /* l'adresse à l'indice numéro depuis l'adresse donnée par   */
  /* maison :                                                  */
  return maisons + numero;
}

int vider_maison(int * maison) {
  /* Lecture du contenu référencé par maison */
  int v = *maison;
  /* Écriture du contenu référencé par maison */
  *maison = 0;
  return v;
}

void vider_camion(int * camion, int * maison) {
  /* Opération sur les contenus référencés par maison et       */
  /* camion :                                                  */
  *maison += *camion;
  *camion = 0;
}

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