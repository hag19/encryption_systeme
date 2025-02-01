#include <stdio.h>
#include <stdlib.h>

int main() {
  const char * path = "nombre.bin";
  int compteur = 0;
  /* TODO : compteur le nombre de fois où le programme est lancé */
  /* TODO : maintenir ce compteur en écriture avec fread et fwrite */
  printf("Programme lancé %d fois\n", compteur);
  exit(EXIT_SUCCESS);
}