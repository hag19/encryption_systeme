#include "../include/List.h"

#include <stdlib.h>

List List_empty() {
	return NULL;
}

void List_free(List * list) {
	/* TODO */
}

List List_alloc(void * value, List next) {
	/* TODO */
	return NULL;
}

void * List_add(List * list, void * value) {
	/* TODO */
	return NULL;
}

void * List_remove(List * list, void * value) {
	/* TODO */
	return NULL;
}

void List_foreach(List list, void (*process)(void *)) {
	/* TODO */
}

void * List_predicate(List list, int (*predicate)(void *)) {
	/* TODO */
	return NULL;
}