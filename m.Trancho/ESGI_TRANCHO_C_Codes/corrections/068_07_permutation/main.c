/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 68.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void init(char alpha[27]) {
  int i;
  for(i = 0; i < 26; ++i) {
    alpha[i] = 'a' + i;
  }
  alpha[i] = '\0';
}

void permutate(char alpha[27]) {
  int first, second;
  char tmp;
  int i;
  for(i = 0; i < 1000; ++i) {
    first = rand() % 26;
    second = rand() % 26;
    tmp = alpha[first];
    alpha[first] = alpha[second];
    alpha[second] = tmp;
  }
}

void inverse(char alpha[27], char ialpha[27]) {
  int i;
  for(i = 0; i < 26; ++i) {
    ialpha[alpha[i] - 'a'] = 'a' + i;
  }
}

void apply(char alpha[27], char texte[]) {
  int i;
  for(i = 0; texte[i] != '\0'; ++i) {
    if('a' <= texte[i] && texte[i] <= 'z')
      texte[i] = alpha[texte[i] - 'a'];
    else if('A' <= texte[i] && texte[i] <= 'Z')
      texte[i] = alpha[texte[i] - 'A'] + 'A' - 'a';
  }
}

int main(int argc, char * argv[]) {
  srand(time(NULL));
  char balpha[27];
  char ialpha[27];
  init(balpha);
  init(ialpha);
  if(argc <= 1 || (argc <= 2 && strcmp(argv[1], "decode") == 0)) {
    printf("Entrez une commande du type :\n"
    " %s [ACTION] [optionnel : ALPHABET]\n"
    "Avec [ACTION] :\n"
    " \"alpha\" : génère une permutation d'alphabet.\n"
    " \"code\" : encode le texte par l'alphabet.\n"
    " \"decode\" : décode le texte depuis l'alphabet.\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char * alpha = (argc > 2) ? argv[2] : balpha;
  char * action = argv[1];
  
  permutate(balpha);
  inverse(alpha, ialpha);
  printf("alpha  : \"%s\"\n", alpha);
  printf("ialpha : \"%s\"\n", ialpha);
  
  if(strcmp(action, "alpha") == 0) {
    exit(EXIT_SUCCESS);
  }
  
  char texte[2048];
  printf("Saisir une ligne : ");
  scanf("%[^\n]", texte);
  printf("Texte        : \"%s\"\n", texte);
  if(strcmp(action, "code") == 0) {
    apply(alpha, texte);
    printf("Texte codé   : \"%s\"\n", texte);
  }
  if(strcmp(action, "decode") == 0) {
    apply(ialpha, texte);
    printf("Texte décodé : \"%s\"\n", texte);
  }
  exit(EXIT_SUCCESS);
}