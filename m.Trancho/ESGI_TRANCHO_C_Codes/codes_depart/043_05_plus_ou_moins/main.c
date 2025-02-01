#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  const int max = 1001;
  int nombre = rand() % max;
  /* À vous de jouer */
  exit(EXIT_SUCCESS);
}