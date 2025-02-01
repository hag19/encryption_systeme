/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include "../include/type_float.h"

#include <math.h>

static int TypeDataFloat_copier(float * dest, const float * src);
static void TypeDataFloat_free(float * elem);
static void TypeDataFloat_afficher(FILE * flow, const float * elem);
static int TypeDataFloat_compare(const float * first, const float * second);
static unsigned long TypeDataFloat_hash(const float * elem);
static char * TypeDataFloat_getType();

TypeData TypeDataFloat() {
  TypeData data;
  data.size = sizeof(float);
  data.copier = (int (*)(void *, const void *))TypeDataFloat_copier;
  data.free = (void (*)(void *))TypeDataFloat_free;
  data.afficher = (void (*)(FILE *, const void *))TypeDataFloat_afficher;
  data.compare = (int (*)(const void *, const void *))TypeDataFloat_compare;
  data.hash = (unsigned long (*)(const void *))TypeDataFloat_hash;
  data.getType = TypeDataFloat_getType;
  return data;
}

static int TypeDataFloat_copier(float * dest, const float * src) {
  *dest = *src;
  return 1;
}

static void TypeDataFloat_free(float * elem) {
  /* do nothing */
}

static void TypeDataFloat_afficher(FILE * flow, const float * elem) {
  fprintf(flow, "%g", *elem);
}

static int TypeDataFloat_compare(const float * first, const float * second) {
  if(abs(*first - *second) < 1e-9) {
    return 0;
  }
  if(*first < *second) {
    return -1;
  } else if(*first > *second) {
    return 1;
  }
  return 0;
}

static unsigned long TypeDataFloat_hash(const float * elem) {
  return *((int*)elem);
}

static char * TypeDataFloat_getType() {
  return "float";
}
