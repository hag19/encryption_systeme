/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 128.
 */

#include "bitbuffer.h"

#include <stdlib.h>

BitBuffer BitBuffer_creer() {
  BitBuffer buffer;
  buffer.data = NULL;
  buffer.cursor = 0;
  buffer.capacite = 0;
  return buffer;
}

int BitBuffer_update(BitBuffer * buffer, unsigned int adding_bits) {
  int size = (buffer->cursor + adding_bits + 8 * sizeof(unsigned long)) / (8 * sizeof(unsigned long));
  if(size < buffer->capacite) {
    return 1;
  }
  int newCapacite = size * 2 + 10;
  unsigned long * tmp = NULL;
  if((tmp = (unsigned long *)realloc(buffer->data, newCapacite * sizeof(unsigned long))) == NULL) {
    return 0;
  }
  buffer->data = tmp;
  buffer->capacite = newCapacite;
  return 1;
}

int BitBuffer_write(BitBuffer * buffer, unsigned long data, unsigned int bits) {
  unsigned long mask = 0xffffffffffffffff;
  if(! BitBuffer_update(buffer, bits)) {
    return 0;
  }
  unsigned long offset = buffer->cursor / (8 * sizeof(unsigned long));
  unsigned long bitoffset = buffer->cursor % (8 * sizeof(unsigned long));
  buffer->data[offset] &= ~(mask << bitoffset);
  buffer->data[offset] |= data << bitoffset;
  if(bitoffset + bits >= (8 * sizeof(unsigned long))) {
    ++offset;
    buffer->data[offset] &= ~(mask >> (8 * sizeof(unsigned long) - bitoffset));
    buffer->data[offset] |= data >> (8 * sizeof(unsigned long) - bitoffset);
  }
  buffer->cursor += bits;
  return 1;
}

int BitBuffer_read(BitBuffer * buffer, unsigned long * data, unsigned int bits) {
  if(bits > buffer->cursor) {
    return 0;
  }
  unsigned long mask = 0xffffffffffffffff;
  unsigned long offset = buffer->cursor / (8 * sizeof(unsigned long));
  *data = buffer->data[0] & (mask >> (8 * sizeof(unsigned long) - bits));
  unsigned long i;
  for(i = 0; i <= offset; ++i) {
    buffer->data[i] >>= bits;
    if(i + 1 > offset) {
      continue;
    }
    buffer->data[i] |= buffer->data[i + 1] << (8 * sizeof(unsigned long) - bits);
  }
  buffer->cursor -= bits;
  return 1;
}

void BitBuffer_print(FILE * flow, const BitBuffer * buffer) {
  long c = buffer->cursor;
  for(--c; c >= 0; --c) {
    fputc((buffer->data[c / (8 * sizeof(unsigned long))] & ((unsigned long)1 << (c % (8 * sizeof(unsigned long))))) ? '1' : '0', flow);
  }
  fputc('\n', flow);
}

void BitBuffer_free(BitBuffer * buffer) {
  if(buffer->data == NULL) {
    free(buffer->data);
    buffer->data = NULL;
  }
  buffer->cursor = 0;
  buffer->capacite = 0;
}