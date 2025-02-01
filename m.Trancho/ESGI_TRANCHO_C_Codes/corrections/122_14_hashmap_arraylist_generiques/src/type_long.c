/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include "../include/type_long.h"

static int TypeDataLong_copier(long * dest, const long * src);
static void TypeDataLong_free(long * elem);
static void TypeDataLong_afficher(FILE * flow, const long * elem);
static int TypeDataLong_compare(const long * first, const long * second);
static unsigned long TypeDataLong_hash(const long * elem);
static char * TypeDataLong_getType();

TypeData TypeDataLong() {
  TypeData data;
  data.size = sizeof(long);
  data.copier = (int (*)(void *, const void *))TypeDataLong_copier;
  data.free = (void (*)(void *))TypeDataLong_free;
  data.afficher = (void (*)(FILE *, const void *))TypeDataLong_afficher;
  data.compare = (int (*)(const void *, const void *))TypeDataLong_compare;
  data.hash = (unsigned long (*)(const void *))TypeDataLong_hash;
  data.getType = TypeDataLong_getType;
  return data;
}

static int TypeDataLong_copier(long * dest, const long * src) {
  *dest = *src;
  return 1;
}

static void TypeDataLong_free(long * elem) {
  /* do nothing */
}

static void TypeDataLong_afficher(FILE * flow, const long * elem) {
  fprintf(flow, "%ld", *elem);
}

static int TypeDataLong_compare(const long * first, const long * second) {
  if(*first < *second) {
    return -1;
  } else if(*first > *second) {
    return 1;
  }
  return 0;
}

static unsigned long TypeDataLong_hash(const long * elem) {
  return *elem;
}

static char * TypeDataLong_getType() {
  return "long";
}
