/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 62.
 */

#include <stdio.h>
#include <stdlib.h>

int esgi_strlen(const char texte[]);
void esgi_strcpy(char destination[], const char source[]);
void esgi_strcat(char destination[], const char source[]);
int esgi_strcmp(const char first[], const char second[]);

int main() {
  char texte[] = "Welcome to ESGI !";
  char hello[] = "Hello";
  char copie[50];
  printf("esgi_strlen(\"%s\") = %d\n", texte, esgi_strlen(texte));
  esgi_strcpy(copie, "Eleve, ");
  printf("copie = \"%s\"\n", copie);
  esgi_strcat(copie, texte);
  printf("copie = \"%s\"\n", copie);
  printf("esgi_strcmp(\"Hello\", \"Hello\") = %d = 0\n", esgi_strcmp(hello, "Hello"));
  printf("esgi_strcmp(\"Hello\", \"Bonjour\") = %d > 0\n", esgi_strcmp(hello, "Bonjour"));
  printf("esgi_strcmp(\"Hello\", \"Hell\") = %d > 0\n", esgi_strcmp(hello, "Hell"));
  printf("esgi_strcmp(\"Bonjour\", \"Hello\") = %d < 0\n", esgi_strcmp("Bonjour", hello));
  exit(EXIT_SUCCESS);
}

int esgi_strlen(const char texte[]) {
  int i;
  /* Nous parcourons la chaîne de caractères jusqu'au marqueur */
  /* de fin.                                                   */
  for(i = 0; texte[i] != '\0'; ++i) {
  }
  return i;
}

void esgi_strcpy(char destination[], const char source[]) {
  int i;
  /* Nous copions individuellement les caractères jusqu'à      */
  /* atteindre le marqueur de fin.                             */
  for(i = 0; source[i] != '\0'; ++i) {
    destination[i] = source[i];
  }
  /* Nous pensons à l'ajouter en fin de la chaîne. */
  destination[i] = '\0';
}

void esgi_strcat(char destination[], const char source[]) {
  int i;
  /* Nous recherchons la position du marqueur de fin de la     */
  /* chaîne destination.                                       */
  int offset = esgi_strlen(destination);
  /* Nous copions les caractères de la chaîne source           */
  /* relativement à la fin de destination.                     */
  for(i = 0; source[i] != '\0'; ++i) {
    destination[i + offset] = source[i];
  }
  destination[i + offset] = '\0';
}

int esgi_strcmp(const char first[], const char second[]) {
  int i;
  /* Tant que les deux chaînes fournissent des caractères */
  for(i = 0; first[i] != '\0' && second[i] != '\0'; ++i) {
    /* S'ils sont différents, nous déterminons la précédence   */
    /* lexicographique entre les chaînes.                      */
    if(first[i] < second[i]) {
      return -1;
    } else if(first[i] > second[i]) {
      return 1;
    }
    /* Sinon les caractères sont identiques. */
  }
  /* Nous gérons le cas où une chaîne serait préfixe de        */
  /* l'autre.                                                  */
  if(first[i] < second[i]) {
    return -1;
  } else if(first[i] > second[i]) {
    return 1;
  } else {
    return 0;
  }
}