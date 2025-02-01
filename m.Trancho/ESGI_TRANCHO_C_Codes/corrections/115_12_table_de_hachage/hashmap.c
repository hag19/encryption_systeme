/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 115.
 */

#include "hashmap.h"

#include <stdlib.h>

typedef struct HashMapElement HME;
struct HashMapElement {
  int key;
  int value;
  HME * next;
};

struct HashMap {
  HME ** data;
  int capacite;
};

static HME * HME_alloc(int key, int value, HME * next);

static HME * HME_rechercher(HME * root, int key);

static void HME_free(HME ** node);

static HME * HME_alloc(int key, int value, HME * next) {
  HME * res = NULL;
  if((res = (HME *)malloc(sizeof(HME))) == NULL) {
    return NULL;
  }
  res->key = key;
  res->value = value;
  res->next = next;
  return res;
}

static HME * HME_rechercher(HME * root, int key) {
  for(; root != NULL; root = root->next) {
    if(root->key == key) {
      return root;
    }
  }
  return NULL;
}

static void HME_free(HME ** node) {
  if(node == NULL || *node == NULL) {
    return;
  }
  HME_free(&((*node)->next));
  free(*node);
  *node = NULL;
}

/* HashMap section */

HashMap * HashMap_creer(int capacite) {
  HashMap * res = NULL;
  if((res = (HashMap *)malloc(sizeof(HashMap))) == NULL) {
    return NULL;
  }
  if((res->data = (HME **)calloc(capacite, sizeof(HME *))) == NULL) {
    free(res);
    return NULL;
  }
  res->capacite = capacite;
  return res;
}

void HashMap_free(HashMap ** hashmap) {
  if(hashmap == NULL || *hashmap == NULL) {
    return;
  }
  int i;
  for(i = 0; i < (*hashmap)->capacite; ++i) {
    HME_free((*hashmap)->data + i);
  }
  free((*hashmap)->data);
  free(*hashmap);
  *hashmap = NULL;
}

static int hashInt(int valeur, int maxi) {
  return valeur % maxi;
}

int HashMap_ajouter(HashMap * hashmap, int valeur) {
  HME * current = NULL;
  int hid = hashInt(valeur, hashmap->capacite);
  if((current = HME_rechercher(*(hashmap->data + hid), valeur)) == NULL) {
    if((current = HME_alloc(valeur, 1, *(hashmap->data + hid))) == NULL) {
      return 0;
    }
    *(hashmap->data + hid) = current;
  } else {
    ++(current->value);
  }
  return 1;
}

void HashMap_afficher(FILE * flow, const HashMap * hashmap) {
  int i;
  HME * current = NULL;
  int count = 0;
  fprintf(flow, "HashMap<int, int> : {");
  for(i = 0; i < hashmap->capacite; ++i) {
    for(current = *(hashmap->data + i); current != NULL; current = current->next) {
      if(count++) fprintf(flow, ", ");
      fprintf(flow, "%d : %d", current->key, current->value);
    }
  }
  fprintf(flow, "}\n");
}

int HashMap_compter(const HashMap * hashmap, int valeur) {
  int hid = hashInt(valeur, hashmap->capacite);
  HME * current = HME_rechercher(*(hashmap->data + hid), valeur);
  return (current) ? (current->value) : 0;
}