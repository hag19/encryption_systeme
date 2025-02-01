/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 122.
 */

#include "../include/hashmap.h"

#include <stdlib.h>

typedef struct HashMapElement HME;
struct HashMapElement {
  void * key;
  void * value;
  HME * next;
};

struct HashMap {
  HME ** data;
  int capacite;
  TypeData keyType;
  TypeData valueType;
};

static HME * HME_alloc(const void * key, const void * value, HME * next, const TypeData * keyType, const TypeData * valueType);

static HME * HME_rechercher(HME * root, const void * key, const TypeData * keyType, const TypeData * valueType);

static void HME_free(HME ** node, const TypeData * keyType, const TypeData * valueType);

static HME * HME_alloc(const void * key, const void * value, HME * next, const TypeData * keyType, const TypeData * valueType) {
  HME * res = NULL;
  if((res = (HME *)malloc(sizeof(HME))) == NULL) {
    return NULL;
  }
  res->key = malloc(keyType->size);
  keyType->copier(res->key, key);
  res->value = malloc(valueType->size);
  valueType->copier(res->value, value);
  res->next = next;
  return res;
}

static HME * HME_rechercher(HME * root, const void * key, const TypeData * keyType, const TypeData * valueType) {
  for(; root != NULL; root = root->next) {
    if(keyType->compare(root->key, key) == 0) {
      return root;
    }
  }
  return NULL;
}

static void HME_free(HME ** node, const TypeData * keyType, const TypeData * valueType) {
  if(node == NULL || *node == NULL) {
    return;
  }
  HME_free(&((*node)->next), keyType, valueType);
  keyType->free((*node)->key);
  valueType->free((*node)->value);
  free((*node)->key);
  free((*node)->value);
  free(*node);
  *node = NULL;
}

/* HashMap section */

HashMap * HashMap_creer(TypeData keyType, TypeData valueType, int capacite) {
  HashMap * res = NULL;
  if((res = (HashMap *)malloc(sizeof(HashMap))) == NULL) {
    return NULL;
  }
  if((res->data = (HME **)calloc(capacite, sizeof(HME *))) == NULL) {
    free(res);
    return NULL;
  }
  res->capacite = capacite;
  res->keyType = keyType;
  res->valueType = valueType;
  return res;
}

void HashMap_free(HashMap ** hashmap) {
  if(hashmap == NULL || *hashmap == NULL) {
    return;
  }
  int i;
  for(i = 0; i < (*hashmap)->capacite; ++i) {
    HME_free((*hashmap)->data + i, &((*hashmap)->keyType), &((*hashmap)->valueType));
  }
  free((*hashmap)->data);
  free(*hashmap);
  *hashmap = NULL;
}

int HashMap_ajouter(HashMap * hashmap, const void * key, const void * valeur) {
  HME * current = NULL;
  unsigned long hid = hashmap->keyType.hash(key) % hashmap->capacite;
  if((current = HME_rechercher(*(hashmap->data + hid), key, &(hashmap->keyType), &(hashmap->valueType))) == NULL) {
    if((current = HME_alloc(key, valeur, *(hashmap->data + hid), &(hashmap->keyType), &(hashmap->valueType))) == NULL) {
      return 0;
    }
    *(hashmap->data + hid) = current;
  } else {
    hashmap->valueType.copier(current->value, valeur);
  }
  return 1;
}

void HashMap_afficher(FILE * flow, const HashMap * hashmap) {
  int i;
  HME * current = NULL;
  int count = 0;
  fprintf(flow, "HashMap<%s, %s> : {", hashmap->keyType.getType(), hashmap->valueType.getType());
  for(i = 0; i < hashmap->capacite; ++i) {
    for(current = *(hashmap->data + i); current != NULL; current = current->next) {
      if(count++) fprintf(flow, ", ");
      hashmap->keyType.afficher(flow, current->key);
      fprintf(flow, " : ");
      hashmap->valueType.afficher(flow, current->value);
    }
  }
  fprintf(flow, "}");
}

int HashMap_rechercher(const HashMap * hashmap, const void * valeur, void * res) {
  unsigned long hid = hashmap->keyType.hash(valeur) % hashmap->capacite;
  HME * current = HME_rechercher(*(hashmap->data + hid), valeur, &(hashmap->keyType), &(hashmap->valueType));
  return (current) ? (hashmap->valueType.copier(res, current->value)) : 0;
}