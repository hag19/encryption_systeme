/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 64.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  char buffer[1024];
  printf("Entrez du texte : ");
  scanf("%[^\n]", buffer);
  printf("Texte : \"%s\"\n", buffer);
  int count;
  char c;
  int i;
  for(c = 'a'; c <= 'z'; ++c) {
    count = 0;
    for(i = 0; buffer[i] != '\0'; ++i) {
      if(buffer[i] == c || buffer[i] == (c + 'A' - 'a')) {
        ++count;
      }
    }
    if(count > 0) {
      printf("\'%c\' : %d\n", c, count);
    }
  }
  exit(EXIT_SUCCESS);
}