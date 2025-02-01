/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include "../include/arraylist.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct ArrayList {
  void * data;
  int taille;
  int capacite;
  TypeData type;
};

static void * ArrayList_at(const ArrayList * liste, int id) {
  return (unsigned char *)(liste->data) + (id * (liste->type.size));
}

ArrayList * ArrayList_creer(TypeData type, int capacite) {
  ArrayList * res = NULL;
  if((res = (ArrayList *)malloc(sizeof(ArrayList))) == NULL) {
    return NULL;
  }
  if(capacite > 0) {
    if((res->data = malloc(capacite * type.size)) == NULL) {
      free(res);
      return NULL;
    }
  }
  res->capacite = capacite;
  res->taille = 0;
  res->type = type;
  return res;
}

ArrayList * ArrayList_creer_depuis_valeurs(TypeData type, int capacite, ...) {
  ArrayList * liste = NULL;
  if((liste = ArrayList_creer(type, capacite)) == NULL)
    return NULL;
  int i;
  va_list ap;
  va_start(ap, capacite);
  for(i = 0; i < capacite; ++i) {
    if(! ArrayList_ajouter(liste, va_arg(ap, const void *))) {
      ArrayList_free(&liste);
      return NULL;
    }
  }
  va_end(ap);
  return liste;
}

void ArrayList_free(ArrayList ** arraylist) {
  if(arraylist == NULL || *arraylist == NULL) {
    return;
  }
  if((*arraylist)->data != NULL) {
    int i;
    for(i = 0; i < (*arraylist)->taille; ++i) {
      (*arraylist)->type.free(ArrayList_at(*arraylist, i));
    }
    free((*arraylist)->data);
  }
  free(*arraylist);
  *arraylist = NULL;
}

static int ArrayList_update_capacity(ArrayList * liste) {
  if(liste->taille < liste->capacite) {
    return 1;
  }
  void * tmp = NULL;
  int newCap = liste->capacite * 2 + 10;
  if((tmp = realloc(liste->data, newCap * liste->type.size)) == NULL) {
    return 0;
  }
  liste->data = tmp;
  liste->capacite = newCap;
  return 1;
}

int ArrayList_ajouter(ArrayList * liste, const void * valeur) {
  if(! ArrayList_update_capacity(liste)) {
    return 0;
  }
  liste->type.copier(ArrayList_at(liste, liste->taille), valeur);
  ++(liste->taille);
  return 1;
}

void ArrayList_afficher(FILE * flow, const ArrayList * liste) {
  int i;
  fprintf(flow, "ArrayList<%s> : [", liste->type.getType());
  for(i = 0; i < liste->taille; ++i) {
    if(i) fprintf(flow, ", ");
    liste->type.afficher(flow, ArrayList_at(liste, i));
  }
  fprintf(flow, "]");
}

int ArrayList_compter(const ArrayList * liste, const void * valeur) {
  int count = 0;
  int i;
  for(i = 0; i < liste->taille; ++i) {
    if(liste->type.compare(ArrayList_at(liste, i), valeur))
      ++count;
  }
  return count;
}

static int TypeDataArrayList_copier(ArrayList ** dest, const ArrayList ** src);
static void TypeDataArrayList_free(ArrayList ** elem);
static void TypeDataArrayList_afficher(FILE * flow, const ArrayList ** elem);
static int TypeDataArrayList_compare(const ArrayList ** first, const ArrayList ** second);
static unsigned long TypeDataArrayList_hash(const ArrayList ** elem);
static char * TypeDataArrayList_getType();

TypeData TypeDataArrayList() {
  TypeData data;
  data.size = sizeof(ArrayList *);
  data.copier = (int (*)(void *, const void *))TypeDataArrayList_copier;
  data.free = (void (*)(void *))TypeDataArrayList_free;
  data.afficher = (void (*)(FILE *, const void *))TypeDataArrayList_afficher;
  data.compare = (int (*)(const void *, const void *))TypeDataArrayList_compare;
  data.hash = (unsigned long (*)(const void *))TypeDataArrayList_hash;
  data.getType = TypeDataArrayList_getType;
  return data;
}

static int TypeDataArrayList_copier(ArrayList ** dest, const ArrayList ** src) {
  if((*dest = ArrayList_creer((*src)->type, (*src)->capacite)) == NULL)
    return 0;
  memcpy((*dest)->data, (*src)->data, (*src)->capacite * (*src)->type.size);
  (*dest)->taille = (*src)->taille;
  return 1;
}

static void TypeDataArrayList_free(ArrayList ** elem) {
  ArrayList_free(elem);
}

static void TypeDataArrayList_afficher(FILE * flow, const ArrayList ** elem) {
  ArrayList_afficher(flow, *elem);
}

static int TypeDataArrayList_compare(const ArrayList ** first, const ArrayList ** second) {
  int i;
  for(i = 0; i < (*first)->taille && i < (*second)->taille; ++i) {
    if((*first)->type.compare(ArrayList_at(*first, i), ArrayList_at(*second, i)) < 0) {
      return -1;
    } else if((*first)->type.compare(ArrayList_at(*first, i), ArrayList_at(*second, i)) > 0) {
      return 1;
    }
  }
  if((*first)->taille < (*second)->taille) {
    return -1;
  } else if((*first)->taille > (*second)->taille) {
    return 1;
  }
  return 0;
}

static unsigned long TypeDataArrayList_hash(const ArrayList ** elem) {
  unsigned long c = 0;
  int i;
  for(i = 0; i < (*elem)->taille; ++i) {
    c = c * 31 + (*elem)->type.hash(ArrayList_at(*elem, i));
  }
  return c;
}

static char * TypeDataArrayList_getType() {
  return "ArrayList";
}
