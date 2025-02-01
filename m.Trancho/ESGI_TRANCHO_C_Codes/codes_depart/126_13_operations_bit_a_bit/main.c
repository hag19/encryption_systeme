#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned char entier8;
  unsigned int entier32;
  unsigned int entier32bis;
  unsigned long entier64;
  int test;
  
  /* TODO : entier32 15e bit à 1,autres à 0 */
  printf("%08x (15e bit à 1)\n", entier32);
  /* TODO : entier32 14e bit à 0,autres à 1 */
  printf("%08x (14e bit à 0)\n", entier32);
  
  /* TODO : entier64 43e bit à 1,autres à 0 */
  printf("%016lx (43e bit à 1)\n", entier64);
  /* TODO : entier64 3e bit à 0,autres à 1 */
  printf("%016lx (3e bit à 0)\n", entier64);
  
  /* TODO : entier32 13e et 1e bit à 1,autres à 0 */
  printf("%08x (13e et 12e bit à 1)\n", entier32);
  
  /* TODO : entier32 mettre le 12e bit à 0 sans changer les autres bits */
  printf("%08x (12e bit à 0)\n", entier32);
  
  /* TODO : entier32 changer le 13e bit sans changer les autres bits */
  printf("%08x (changement 13e bit)\n", entier32);
  
  entier8 = 0x1;
  /* TODO : entier32 affecter au 11e bit la valeur de entier8 */
  printf("%08x (affectation 11e bit)\n", entier32);
  
  /* TODO : mettre vrai dans test si le 11e bit de entier32 est 1 */
  printf("%08x (test 11e bit : %d)\n", entier32, test);
  
  entier32 = 0xFF;
  /* TODO : mettre vrai dans test si les 3 bits de poids faible de entier32 sont 1 */
  printf("%08x (test des 3 bits de poids faible à 1 : %d)\n", entier32, test);
  
  entier32 = 0xF0;
  /* TODO : mettre vrai dans test si les 4 bits de poids faible de entier32 sont 0 */
  printf("%08x (test des 4 bits de poids faible à 0 : %d)\n", entier32, test);
  
  entier32 = 0xFFE80F12;
  entier32bis = 0x0017F0ED;
  
  /* TODO : mettre vrai dans test si les bits de entier32 et entier32bis sont differents  */
  printf("%08x et %08x (test bits tous differents : %d)\n", entier32, entier32bis, test);
  
  exit(EXIT_SUCCESS);
}