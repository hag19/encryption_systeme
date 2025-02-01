#include <stdio.h>
#include <stdlib.h>

int main() {
  char nom[100], prenom[50];
  char * full_name = NULL;
  printf("Bonjour, entrez votre nom et prénom : ");
  scanf("%s %s", nom, prenom);
  full_name = prenom + ' ' + nom;
  printf("Vous êtes donc %s !\n", full_name);
  exit(EXIT_SUCCESS);
}