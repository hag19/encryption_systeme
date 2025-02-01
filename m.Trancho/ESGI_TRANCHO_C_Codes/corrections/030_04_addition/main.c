/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 30.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int entree = 0;
  int plat = 0;
  int dessert = 0;
  double addition = 0.;
  printf("Voici nos entrées : \n 1. (1.50 €) Salade racontée.\n 2. (2.50 €) Oeufs embrouillés.\n 0. Non merci.\nVotre choix : ");
  scanf("%d", &entree);
  printf("Voici nos plats : \n 1. (12 €) Pizza spéciale informaticien.\n 2. (8 €) Pâtes spéciales étudiants.\n 0. Non merci.\nVotre choix : ");
  scanf("%d", &plat);
  printf("Voici nos desserts : \n 1. (2.50 €) La cerise sur le gâteau.\n 0. Non merci.\nVotre choix : ");
  scanf("%d", &dessert);
  if(entree == 0 && plat == 0 && dessert == 0) {
    printf("Bien, passez une bonne journée.\n");
    exit(EXIT_SUCCESS);
  }
  printf("Votre commande : \n");
  switch(entree) {
    case 1 : {
      printf(" - (1.50 €) Salade racontée.\n");
      addition += 1.5;
    } break;
    case 2 : {
      printf(" - (2.5 €) Oeufs embrouillés.\n");
      addition += 2.5;
    } break;
    default : break;
  }
  switch(plat) {
    case 1 : {
      printf(" - (12 €) Pizza spéciale informaticien.\n");
      addition += 12;
    } break;
    case 2 : {
      printf(" - (8 €) Pâtes spéciales étudiants.\n");
      addition += 8;
    } break;
    default : {
      printf(" - Pas de plat...\n");
    } break;
  }
  switch(dessert) {
    case 1 : {
      printf(" - (2.5 €) La cerise sur le gâteau.\n");
      addition += 2.5;
    } break;
    default : break;
  }
  printf("Total hors taxes : %.2f €\n", addition);
  addition *= 1.20;
  printf("Total TTC %.2f € (TVA à 20%%)\n", addition);
  
  exit(EXIT_SUCCESS);
}