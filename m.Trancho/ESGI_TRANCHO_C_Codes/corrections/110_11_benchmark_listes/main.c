/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 89.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList * LinkedList;
struct LinkedList {
  int value;
  LinkedList next;
};

/* Renvoie une liste vide */
/* Complexité : O(1) */
LinkedList LL_empty();

/* Libère la liste */
/* Complexité : O(n) */
void LL_free(LinkedList * liste);

/* Ajoute un élément en fin */
/* Complexité : O(n) */
int LL_add_tail(LinkedList * liste, int value);

/* Ajoute un élément en tête */
/* Complexité : O(1) */
int LL_add_head(LinkedList * liste, int value);

/* Ajoute un élément à une position donnée */
/* Complexité : O(n) */
int LL_insert(LinkedList * liste, int id, int value);

/* Supprime l'élément en fin */
/* Complexité : O(n) */
int LL_pop_tail(LinkedList * liste, int * value);

/* Supprime l'élément en tête */
/* Complexité : O(1) */
int LL_pop_head(LinkedList * liste, int * value);

/* Supprime l'élément à une position donnée */
/* Complexité : O(n) */
int LL_delete(LinkedList * liste, int id, int * value);

/* Affiche la liste */
/* Complexité : O(n) */
void LL_print(FILE * flow, const LinkedList * liste);

typedef struct ArrayList ArrayList;
struct ArrayList {
  int * values;
  int size;
  int capacite;
};

/* Renvoie une liste vide */
/* Complexité : O(1) */
ArrayList AL_empty();

/* Libère la liste */
/* Complexité : O(1) */
void AL_free(ArrayList * liste);

/* Ajoute un élément en fin */
/* Complexité : O(1) */
int AL_add_tail(ArrayList * liste, int value);

/* Ajoute un élément en tête */
/* Complexité : O(n) */
int AL_add_head(ArrayList * liste, int value);

/* Ajoute un élément à une position donnée */
/* Complexité : O(n) */
int AL_insert(ArrayList * liste, int id, int value);

/* Supprime l'élément en fin */
/* Complexité : O(1) */
int AL_pop_tail(ArrayList * liste, int * value);

/* Supprime l'élément en tête */
/* Complexité : O(n) */
int AL_pop_head(ArrayList * liste, int * value);

/* Supprime l'élément à une position donnée */
/* Complexité : O(n) */
int AL_delete(ArrayList * liste, int id, int * value);

/* Affiche la liste */
/* Complexité : O(n) */
void AL_print(FILE * flow, const ArrayList * liste);

int main() {
  int v;
  
  ArrayList al = AL_empty();
  AL_print(stdout, &al);
  AL_add_tail(&al, 1);
  AL_print(stdout, &al);
  AL_add_tail(&al, 2);
  AL_print(stdout, &al);
  AL_add_head(&al, -1);
  AL_print(stdout, &al);
  AL_add_head(&al, -2);
  AL_print(stdout, &al);
  AL_insert(&al, 2, 0);
  AL_print(stdout, &al);
  AL_pop_tail(&al, &v);
  printf("v : %d; ", v);
  AL_print(stdout, &al);
  AL_pop_head(&al, &v);
  printf("v : %d; ", v);
  AL_print(stdout, &al);
  AL_delete(&al, 1, &v);
  printf("v : %d; ", v);
  AL_print(stdout, &al);
  AL_free(&al);
  
  LinkedList ll = LL_empty();
  LL_print(stdout, &ll);
  LL_add_tail(&ll, 1);
  LL_print(stdout, &ll);
  LL_add_tail(&ll, 2);
  LL_print(stdout, &ll);
  LL_add_head(&ll, -1);
  LL_print(stdout, &ll);
  LL_add_head(&ll, -2);
  LL_print(stdout, &ll);
  LL_insert(&ll, 2, 0);
  LL_print(stdout, &ll);
  LL_pop_tail(&ll, &v);
  printf("v : %d; ", v);
  LL_print(stdout, &ll);
  LL_pop_head(&ll, &v);
  printf("v : %d; ", v);
  LL_print(stdout, &ll);
  LL_delete(&ll, 1, &v);
  printf("v : %d; ", v);
  LL_print(stdout, &ll);
  LL_free(&ll);
  
  exit(EXIT_SUCCESS);
}

/* Allocation d'un maillon de la liste */
static LinkedList LL_alloc(int value, LinkedList next) {
  LinkedList res = NULL;
  if((res = (LinkedList)malloc(sizeof(struct LinkedList))) == NULL) {
    return NULL;
  }
  res->value = value;
  res->next = next;
  return res;
}

/* Une liste vide correspond à NULL : aucun maillons */
LinkedList LL_empty() {
  return NULL;
}

/* Nous libérons récursivement les maillons de la liste */
void LL_free(LinkedList * liste) {
  if(liste == NULL || *liste == NULL) {
    return;
  }
  LL_free(&((*liste)->next));
  free(*liste);
}

/* Pour ajouter en fin, nous avons besoin de parcourir tous    */
/* les éléments de la liste                                    */
/* Nous profitons d'avoir un déréférencement pour assigner le  */
/* nouveau maillon en fin.                                     */
int LL_add_tail(LinkedList * liste, int value) {
  for(; *liste != NULL; liste = &((*liste)->next)) ;
  if((*liste = LL_alloc(value, NULL)) == NULL) {
    return 0;
  }
  return 1;
}

/* L'ajout en tête se fait instantanément en mettant la liste  */
/* courante en fin d'un nouveau maillon. Notre tête de liste   */
/* devient ce nouveau maillon.                                 */
int LL_add_head(LinkedList * liste, int value) {
  if((*liste = LL_alloc(value, *liste)) == NULL) {
    return 0;
  }
  return 1;
}

/* Nous parcourons autant d'éléments que demandé et insérons   */
/* un nouveau maillon à l'emplacement donné. */
int LL_insert(LinkedList * liste, int id, int value) {
  for(; *liste != NULL && id > 0; liste = &((*liste)->next), --id) ;
  if(id > 0) {
    return 0;
  }
  if((*liste = LL_alloc(value, *liste)) == NULL) {
    return 0;
  }
  return 1;
}

/* Nous parcourons la liste jusqu'à avoir en main le dernier   */
/* maillon.                                                    */
int LL_pop_tail(LinkedList * liste, int * value) {
  if(*liste == NULL) {
    return 0;
  }
  for(; (*liste)->next != NULL; liste = &((*liste)->next)) ;
  *value = (*liste)->value;
  free(*liste);
  *liste = NULL;
  return 1;
}

/* Nous sauvegardons la tête de liste pour la libérer ensuite. */
/* La tête devient l'élément qui suit le premier maillon.      */
int LL_pop_head(LinkedList * liste, int * value) {
  if(*liste == NULL) {
    return 0;
  }
  LinkedList current = *liste;
  *liste = (*liste)->next;
  *value = current->value;
  free(current);
  return 1;
}

int LL_delete(LinkedList * liste, int id, int * value) {
  if(*liste == NULL) {
    return 0;
  }
  for(; (*liste)->next != NULL && id > 0; liste = &((*liste)->next), --id) ;
  if(id > 0) {
    return 0;
  }
  LinkedList current = *liste;
  *liste = (*liste)->next;
  *value = current->value;
  free(current);
  return 1;
}

void LL_print(FILE * flow, const LinkedList * liste) {
  fprintf(flow, "LinkedList : [");
  int i;
  for(i = 0; *liste != NULL; ++i, liste = &((*liste)->next)) {
    if(i) fprintf(flow, ", ");
    fprintf(flow, "%d", (*liste)->value);
  }
  fprintf(flow, "]\n");
}

static int AL_update(ArrayList * liste) {
  if(liste->size < liste->capacite) {
    return 1;
  }
  int newCap = liste->size * 2 + 10;
  int * newValues = NULL;
  if((newValues = (int *)realloc(liste->values, sizeof(int) * newCap)) == NULL) {
    return 0;
  }
  liste->capacite = newCap;
  liste->values = newValues;
  return 1;
}

ArrayList AL_empty() {
  ArrayList res;
  res.values = NULL;
  res.capacite = 0;
  res.size = 0;
  return res;
}

void AL_free(ArrayList * liste) {
  if(liste == NULL) {
    return;
  }
  if(liste->values != NULL) {
    free(liste->values);
    liste->values = NULL;
  }
  liste->capacite = 0;
  liste->size = 0;
}

int AL_add_tail(ArrayList * liste, int value) {
  if(! AL_update(liste)) {
    return 0;
  }
  liste->values[(liste->size)++] = value;
  return 1;
}

int AL_add_head(ArrayList * liste, int value) {
  if(! AL_update(liste)) {
    return 0;
  }
  int i;
  for(i = liste->size; i > 0; --i) {
    liste->values[i] = liste->values[i - 1];
  }
  liste->values[0] = value;
  (liste->size)++;
  return 1;
}

int AL_insert(ArrayList * liste, int id, int value) {
  if(! AL_update(liste)) {
    return 0;
  }
  int i;
  for(i = liste->size; i > id; --i) {
    liste->values[i] = liste->values[i - 1];
  }
  liste->values[id] = value;
  (liste->size)++;
  return 1;
}

int AL_pop_tail(ArrayList * liste, int * value) {
  if(liste->size <= 0) {
    return 0;
  }
  *value = liste->values[--(liste->size)];
  return 1;
}

int AL_pop_head(ArrayList * liste, int * value) {
  if(liste->size <= 0) {
    return 0;
  }
  *value = liste->values[0];
  int i;
  for(i = 0; i < liste->size - 1; ++i) {
    liste->values[i] = liste->values[i + 1];
  }
  --(liste->size);
  return 1;
}

int AL_delete(ArrayList * liste, int id, int * value) {
  if(liste->size <= 0) {
    return 0;
  }
  *value = liste->values[id];
  int i;
  for(i = id; i < liste->size - 1; ++i) {
    liste->values[i] = liste->values[i + 1];
  }
  --(liste->size);
  return 1;
}

void AL_print(FILE * flow, const ArrayList * liste) {
  fprintf(flow, "ArrayList : [");
  int i;
  for(i = 0; i < liste->size; ++i) {
    if(i) fprintf(flow, ", ");
    fprintf(flow, "%d", liste->values[i]);
  }
  fprintf(flow, "]\n");
}