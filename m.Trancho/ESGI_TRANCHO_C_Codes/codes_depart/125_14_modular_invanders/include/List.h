#ifndef DEF_HEADER_ESGI_SPACE_CRAFT_LIST
#define DEF_HEADER_ESGI_SPACE_CRAFT_LIST

#include <stdlib.h>

typedef struct List * List;
struct List {
	/* TODO */
};

List List_empty();

void List_free(List * list);

List List_alloc(void * value, List next);

void * List_add(List * list, void * value);

void * List_remove(List * list, void * value);

void List_foreach(List list, void (*process)(void *));

void * List_predicate(List list, int (*predicate)(void *));

#endif