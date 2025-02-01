#include <stdio.h>
#include <stdlib.h>

int main() {
  /* TODO : faire fonctionner le code sans changer les types de variable et pointeur */
  int variable = 42;
  unsigned long pointeur = &variable;
  *pointeur = 1337;
  /* TODO : variable doit valoir 1337 */
  printf("%d = 1337 ?\n", variable);
  exit(EXIT_SUCCESS);
}