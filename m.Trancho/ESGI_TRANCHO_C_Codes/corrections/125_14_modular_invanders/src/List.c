/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 125.
 */

#include "../include/List.h"

#include <stdlib.h>
#include <assert.h>

List List_empty() {
  return NULL;
}

void List_free(List * list) {
  if(*list == NULL) {
    return;
  }
  List_free(&((*list)->next));
  free((*list)->value);
  free(*list);
  *list = NULL;
}

List List_alloc(void * value, List next) {
  List list = NULL;
  assert(list = (List)malloc(sizeof(struct List)));
  list->value = value;
  list->next = next;
  return list;
}

void * List_add(List * list, void * value) {
  *list = List_alloc(value, *list);
  return value;
}

void * List_remove(List * list, void * value) {
  for(; *list != NULL; list = &((*list)->next)) {
    if((*list)->value == value) {
      List current = *list;
      *list = (*list)->next;
      free(current);
      return value;
    }
  }
  return NULL;
}

void List_foreach(List list, void (*process)(void *)) {
  for(; list != NULL; list = list->next) {
    (*process)(list->value);
  }
}

void * List_predicate(List list, int (*predicate)(void *)) {
  for(; list != NULL; list = list->next) {
    if((*predicate)(list->value)) {
      return list->value;
    }
  }
  return NULL;
}