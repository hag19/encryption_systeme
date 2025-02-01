/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 79.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char nom[100], prenom[50];
  char * full_name = NULL;
  printf("Bonjour, entrez votre nom et prénom : ");
  scanf("%s %s", nom, prenom);
  
  /* full_name référence une adresse, ceci induit la nécessité */
  /* de pointer sur des données valides.                       */
  /* Le choix est d'allouer dynamiquement la plage mémoire qui */
  /* pourra accueillir la concaténation des chaînes.           */
  
  /* Il faut la taille des chaînes et la place pour l'espace   */
  /* et marqueur de fin :                                      */
  int size = 2 + strlen(nom) + strlen(prenom);
  /* Allocation dynmatique propre de la plage mémoire          */
  /* demandée :                                                */
  if((full_name = (char *)malloc(sizeof(char) * size)) == NULL) {
    printf("Allocation impossible.\n");
    exit(EXIT_FAILURE);
  }
  
  /* Opérations sur la chaîne de caractère via opérations de   */
  /* string.h (full_name est une adresse, les opérations       */
  /* d'affectation et arithmétiques joueraient sur l'adresse   */
  /* et non le contenu référencé)                              */
  strcpy(full_name, prenom);
  strcat(full_name, " ");
  strcat(full_name, nom);
  
  printf("Vous êtes donc %s !\n", full_name);
  
  /* Libération de la plage mémoire demandée : */
  free(full_name);
  /* L'adresse n'étant plus valide, elle n'a plus à être       */
  /* connue.                                                   */
  full_name = NULL;
  exit(EXIT_SUCCESS);
}