/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 100.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vigenere(FILE * input, char * cle, int sign, FILE * output) {
  int i, j;
  int value;
  int offset;
  int texte;
  int message;
  /* Nous lisons des caractères dans le fichier tant que nous  */
  /* ne rencontrons pas le marqueur de fin de fichier.         */
  for(i = 0, j = 0; (texte = fgetc(input)) != EOF; ++i) {
  /* Si le caractère est une majuscule */
  if(texte >= 'A' && texte <= 'Z') {
    /* Nous récupérons son décalage par rapport à 'A' de sorte */
    /* que 'A' donne 0, 'B' donne 1, et ainsi de suite.        */
    value = texte - 'A';
    /* Nous mettons le résultat à 'A' pour appliquer le        */
    /* décalage ensuite et conserver la connaissance d'une     */
    /* majuscule.                                              */
    message = 'A';
  } else if(texte >= 'a' && texte <= 'z') {
    /* Nous procédons similairement aux majuscules dans le cas */
    /* d'une lettre minuscule.                                 */
    value = texte - 'a';
    message = 'a';
  } else {
    /* En cas d'un caractère non alphabétique, nous            */
    /* l'imprimons sans appliquer de décalage.                 */
    fputc(texte, output);
    continue;
  }
  /* Nous récupérons le décalage correspondant à la clé. */
  if(cle[j] >= 'A' && cle[j] <= 'Z') {
    offset = cle[j] - 'A';
  } else if(cle[j] >= 'a' && cle[j] <= 'z') {
    offset = cle[j] - 'a';
  }
  /* Nous calculons le décalage depuis la clé. */
  value = ((value + sign * offset) % 26 + 26) % 26;
  /* Nous ajoutons le décalage à la lettre. */
  message += value;
  /* Nous mettons à jour le curseur sur les lettres de la clé. */
  j = (j + 1) % strlen(cle);
  /* Nous imprimons le résultat. */
  fputc(message, output);
  }
}

int main(int argc, char * argv[]) {
  if(argc <= 2) {
    printf("Attendu : %s [FICHIER MESSAGE] [CLE]\n", argv[0]);
    printf("Attendu : %s [FICHIER MESSAGE] [CLE] decode\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  /* Nous ajoutons de la sémantique aux arguments obtenus. */
  char * path = argv[1];
  char * cle = argv[2];
  /* Nous déterminons si le décalage doit s'appliquer vers     */
  /* l'avant ou vers l'arrière.                                */
  int sign = (argc > 3 && strcmp(argv[3], "decode") == 0) ? -1 : 1;
  FILE * input = NULL;
  FILE * output = stdout;
  /* Nous ouvrons le fichier donné en entrée. */
  if((input = fopen(path, "r")) == NULL) {
    fprintf(stderr, "Erreur ouverture \"%s\"\n", path);
    exit(EXIT_FAILURE);
  }
  /* Nous appliquons le codage vigénère depuis la récupération */
  /* dans le fichier.                                          */
  vigenere(input, cle, sign, output);
  fclose(input);
  exit(EXIT_SUCCESS);
}