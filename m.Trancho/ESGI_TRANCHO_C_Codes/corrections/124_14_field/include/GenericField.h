/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#ifndef DEF_HEADER_GENERIC_FIELD
#define DEF_HEADER_GENERIC_FIELD

#include <stdio.h>
#include <stdlib.h>

typedef struct Field Field;
struct Field {
	size_t size;
	void (*fill_addition_neutral)(Field *, void *);
	void (*fill_multiplication_neutral)(Field *, void *);
	void (*fill_addition)(Field *, void *, void *, void *);
	void (*fill_multiplication)(Field *, void *, void *, void *);
  void (*fill_copy)(Field *, void *, void *);
	void (*fill_addition_inverse)(Field *, void *, void *);
	void (*fill_multiplication_inverse)(Field *, void *, void *);
	size_t (*display)(Field *, FILE *, void *);
	void * userData;
};

#endif