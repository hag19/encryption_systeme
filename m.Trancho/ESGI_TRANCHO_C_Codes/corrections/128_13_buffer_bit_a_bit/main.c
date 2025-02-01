/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 128.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bitbuffer.h"

int main() {
  BitBuffer buffer = BitBuffer_creer();
  unsigned long infos[] = {
    1, 0x1,
    5, 0xf,
    16, 0xffff,
    32, 0x18181818,
    5, 0x7,
    16, 0xffff,
    32, 0x18181818,
    5, 0xf,
    1, 0x1,
    1, 0x1,
    1, 0x0,
    1, 0x1,
    1, 0x0,
    1, 0x0,
    1, 0x1,
    16, 0xffff,
    31, 0x8181818,
    5, 0x7,
    31, 0x8181818,
    5, 0xf,
    0
  };
  int i;
  for(i = 0; infos[2 * i] > 0; ++i) {
    BitBuffer_write(&buffer, infos[2 * i + 1], infos[2 * i]);
#ifdef VERBOSE
    BitBuffer_print(stderr, &buffer);
#endif
  }
  unsigned long data = 0;
  for(i = 0; infos[2 * i] > 0; ++i) {
    BitBuffer_read(&buffer, &data, infos[2 * i]);
#ifdef VERBOSE
    BitBuffer_print(stderr, &buffer);
#endif
    printf("(%d) %lx\n", data == infos[2 * i + 1], data);
  }
  BitBuffer_free(&buffer);
  exit(EXIT_SUCCESS);
}