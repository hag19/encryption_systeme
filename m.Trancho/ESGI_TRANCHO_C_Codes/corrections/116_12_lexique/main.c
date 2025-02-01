/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 116.
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#ifndef TEST
int main(int argc, char * argv[]) {

  char * path = NULL;
  if(argc > 1) {
    path = argv[1];
  }
  if(path == NULL) {
    printf("Attente : %s [FICHIER]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  Node * root = NULL;
  FILE * input = NULL;
  if((input = fopen(path, "r")) == NULL) {
    fprintf(stderr, "Erreur d'ouverture de \"%s\"\n", path);
    exit(EXIT_FAILURE);
  }
  char buffer[100];
  while(fscanf(input, "%s", buffer) == 1) {
    Node_ajouter_chaine(&root, buffer);
  }
  Node_afficher(stdout, root);
  Node_afficher_all(stderr, root);
  Node_free(&root);
#else
int main() {
  Node * root = NULL;
  Node_ajouter_chaine(&root, "Test");
  Node_ajouter_chaine(&root, "Preference");
  Node_ajouter_chaine(&root, "Prefixe");
  Node_ajouter_chaine(&root, "Test");
  Node_ajouter_chaine(&root, "Alpha");
  Node_ajouter_chaine(&root, "Alphabet");
  Node_afficher(stdout, root);
  
  Node_afficher_all(stderr, root);
  Node_free(&root);
#endif
  exit(EXIT_SUCCESS);
}