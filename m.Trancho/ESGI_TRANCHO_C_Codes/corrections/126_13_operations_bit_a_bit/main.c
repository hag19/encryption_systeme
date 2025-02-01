/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 126.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned char entier8;
  unsigned int entier32;
  unsigned int entier32bis;
  unsigned long entier64;
  int test;
  
  entier32 = 1 << 14;
  printf("%08x (15e bit à 1)\n", entier32);
  entier32 = ~((unsigned int)1 << 13);
  printf("%08x (14e bit à 0)\n", entier32);
  
  entier64 = (unsigned long)1 << 42;
  printf("%016lx (43e bit à 1)\n", entier64);
  entier64 = ~((unsigned long)1 << 2);
  printf("%016lx (3e bit à 0)\n", entier64);
  
  entier32 = (unsigned int)1 << 12 | (unsigned int)1 << 11;
  printf("%08x (13e et 12e bit à 1)\n", entier32);
  
  entier32 &= ~((unsigned int)1 << 11);
  printf("%08x (12e bit à 0)\n", entier32);
  
  entier32 ^= (unsigned int)1 << 12;
  printf("%08x (changement 13e bit)\n", entier32);
  
  entier8 = 0x1;
  entier32 &= ~((unsigned int)1 << 10);
  entier32 |= (unsigned int)entier8 << 10;
  printf("%08x (affectation 11e bit)\n", entier32);
  
  test = (entier32 & ((unsigned int)1 << 10)) != 0;
  printf("%08x (test 11e bit : %d)\n", entier32, test);
  
  entier32 = 0xFF;
  test = (entier32 & 0x7) == 0x7;
  printf("%08x (test des 3 bits de poids faible à 1 : %d)\n", 
    entier32, test);
  
  entier32 = 0xF0;
  test = (entier32 & 0xF) == 0xF;
  printf("%08x (test des 4 bits de poids faible à 0 : %d)\n", 
    entier32, test);
  
  entier32 = 0xFFE80F12;
  entier32bis = 0x0017F0ED;
  
  test = (entier32 ^ (~entier32bis)) == 0;
  printf("%08x et %08x (test bits tous differents : %d)\n", 
    entier32, entier32bis, test);
  
  exit(EXIT_SUCCESS);
}