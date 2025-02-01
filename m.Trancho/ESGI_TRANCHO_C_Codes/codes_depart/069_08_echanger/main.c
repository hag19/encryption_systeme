#include <stdio.h>
#include <stdlib.h>

void echanger(int first, int second) {
  int temporaire;
  temporaire = first;
  first = second;
  second = temporaire;
}

int main() {
  int first = 42, second = 1337;
  printf("first = %d, second = %d\n", first, second);
  echanger(first, second);
  printf("first = %d, second = %d\n", first, second);
  exit(EXIT_SUCCESS);
}