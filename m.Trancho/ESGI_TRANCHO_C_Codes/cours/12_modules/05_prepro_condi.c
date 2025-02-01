/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG
int main() {
#if defined VERBOSE
  fprintf(stderr, "Entrée dans le main\n");
#endif
#if defined VERBOSE
  printf("42, la réponse à la vie !\n");
#elif defined DEBUG
  printf("42, vous savez pourquoi.\n");
#else
  printf("42 !\n");
#endif
#if defined VERBOSE
  fprintf(stderr, "Sortie du main\n");
#endif
  exit(EXIT_SUCCESS);
}