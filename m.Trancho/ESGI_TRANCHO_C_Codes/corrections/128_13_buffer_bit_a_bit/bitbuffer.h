/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 128.
 */

#ifndef DEF_HEADER_BITBUFFER
#define DEF_HEADER_BITBUFFER

#include <stdio.h>

typedef struct BitBuffer BitBuffer;
struct BitBuffer {
  unsigned long * data;
  long cursor;
  long capacite;
};

BitBuffer BitBuffer_creer();

int BitBuffer_update(BitBuffer * buffer, unsigned int adding_bits);

int BitBuffer_write(BitBuffer * buffer, unsigned long data, unsigned int bits);

int BitBuffer_read(BitBuffer * buffer, unsigned long * data, unsigned int bits);

void BitBuffer_print(FILE * flow, const BitBuffer * buffer);

void BitBuffer_free(BitBuffer * buffer);

#endif