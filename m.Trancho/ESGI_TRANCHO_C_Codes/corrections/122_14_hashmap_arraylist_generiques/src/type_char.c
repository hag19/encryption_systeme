/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include "../include/type_char.h"

static int TypeDataChar_copier(char * dest, const char * src);
static void TypeDataChar_free(char * elem);
static void TypeDataChar_afficher(FILE * flow, const char * elem);
static int TypeDataChar_compare(const char * first, const char * second);
static unsigned long TypeDataChar_hash(const char * elem);
static char * TypeDataChar_getType();

TypeData TypeDataChar() {
  TypeData data;
  data.size = sizeof(char);
  data.copier = (int (*)(void *, const void *))TypeDataChar_copier;
  data.free = (void (*)(void *))TypeDataChar_free;
  data.afficher = (void (*)(FILE *, const void *))TypeDataChar_afficher;
  data.compare = (int (*)(const void *, const void *))TypeDataChar_compare;
  data.hash = (unsigned long (*)(const void *))TypeDataChar_hash;
  data.getType = TypeDataChar_getType;
  return data;
}

static int TypeDataChar_copier(char * dest, const char * src) {
  *dest = *src;
  return 1;
}

static void TypeDataChar_free(char * elem) {
  /* do nothing */
}

static void TypeDataChar_afficher(FILE * flow, const char * elem) {
  fprintf(flow, "\'%c\'", *elem);
}

static int TypeDataChar_compare(const char * first, const char * second) {
  return *first - *second;
}

static unsigned long TypeDataChar_hash(const char * elem) {
  return *elem;
}

static char * TypeDataChar_getType() {
  return "char";
}
