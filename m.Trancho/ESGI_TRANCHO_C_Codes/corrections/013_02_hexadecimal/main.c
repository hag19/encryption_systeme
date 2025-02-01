/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 13.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Sauvegarder fb40 8be9 */
  unsigned int code = 0xfb408be9;
  printf("Code : %u\n", code);
  printf("%X%d\n", 42, 42);
  unsigned long first = 212063991488173;
  unsigned long second = 223196547513038;
  printf("\"if %lX then %lX\"\n", first, second);
  exit(EXIT_SUCCESS);
}