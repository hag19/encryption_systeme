/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include "../include/type_int.h"

static int TypeDataInt_copier(int * dest, const int * src);
static void TypeDataInt_free(int * elem);
static void TypeDataInt_afficher(FILE * flow, const int * elem);
static int TypeDataInt_compare(const int * first, const int * second);
static unsigned long TypeDataInt_hash(const int * elem);
static char * TypeDataInt_getType();

TypeData TypeDataInt() {
  TypeData data;
  data.size = sizeof(int);
  data.copier = (int (*)(void *, const void *))TypeDataInt_copier;
  data.free = (void (*)(void *))TypeDataInt_free;
  data.afficher = (void (*)(FILE *, const void *))TypeDataInt_afficher;
  data.compare = (int (*)(const void *, const void *))TypeDataInt_compare;
  data.hash = (unsigned long (*)(const void *))TypeDataInt_hash;
  data.getType = TypeDataInt_getType;
  return data;
}

static int TypeDataInt_copier(int * dest, const int * src) {
  *dest = *src;
  return 1;
}

static void TypeDataInt_free(int * elem) {
  /* do nothing */
}

static void TypeDataInt_afficher(FILE * flow, const int * elem) {
  fprintf(flow, "%d", *elem);
}

static int TypeDataInt_compare(const int * first, const int * second) {
  return *first - *second;
}

static unsigned long TypeDataInt_hash(const int * elem) {
  return *elem;
}

static char * TypeDataInt_getType() {
  return "int";
}
