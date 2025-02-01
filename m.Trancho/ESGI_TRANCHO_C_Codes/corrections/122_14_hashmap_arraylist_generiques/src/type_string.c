/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include "../include/type_string.h"

#include <string.h>

static int TypeDataString_copier(char ** dest, const char ** src);
static void TypeDataString_free(char ** elem);
static void TypeDataString_afficher(FILE * flow, const char ** elem);
static int TypeDataString_compare(const char ** first, const char ** second);
static unsigned long TypeDataString_hash(const char ** elem);
static char * TypeDataString_getType();

TypeData TypeDataString() {
  TypeData data;
  data.size = sizeof(char *);
  data.copier = (int (*)(void *, const void *))TypeDataString_copier;
  data.free = (void (*)(void *))TypeDataString_free;
  data.afficher = (void (*)(FILE *, const void *))TypeDataString_afficher;
  data.compare = (int (*)(const void *, const void *))TypeDataString_compare;
  data.hash = (unsigned long (*)(const void *))TypeDataString_hash;
  data.getType = TypeDataString_getType;
  return data;
}

static int TypeDataString_copier(char ** dest, const char ** src) {
  if(*src == NULL) {
    *dest = NULL;
    return 1;
  }
  if((*dest = (char *)malloc((1 + strlen(*src)) * sizeof(char))) == NULL) {
    return 0;
  }
  strcpy(*dest, *src);
  return 1;
}

static void TypeDataString_free(char ** elem) {
  if(*elem != NULL) {
    free(*elem);
    *elem = NULL;
  }
}

static void TypeDataString_afficher(FILE * flow, const char ** elem) {
  if(*elem == NULL)
    return;
  fprintf(flow, "\"%s\"", *elem);
}

static int TypeDataString_compare(const char ** first, const char ** second) {
  if(*first == NULL) {
    return (*second == NULL) ? 0 : -1;
  } else if(*second == NULL) {
    return 1;
  }
  return strcmp(*first, *second);
}

static unsigned long TypeDataString_hash(const char ** elem) {
  if(*elem == NULL) {
    return 0;
  }
  unsigned long h = 0;
  const char * current = NULL;
  for(current = *elem; *current != '\0'; ++current) {
    h = 31 * h + *current + 129;
  }
  return h;
}

static char * TypeDataString_getType() {
  return "string";
}
