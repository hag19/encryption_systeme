/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#ifndef DEF_HEADER_TYPE_DATA
#define DEF_HEADER_TYPE_DATA

#include <stdio.h>
#include <stdlib.h>

typedef struct TypeData TypeData;
struct TypeData {
  size_t size;
  int (*copier)(void * dest, const void * src);
  void (*free)(void * elem);
  void (*afficher)(FILE * flow, const void * elem);
  int (*compare)(const void * first, const void * second);
  unsigned long (*hash)(const void * elem);
  char * (*getType)();
};

#endif