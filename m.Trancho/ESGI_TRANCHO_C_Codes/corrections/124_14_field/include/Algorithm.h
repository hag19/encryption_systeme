/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#ifndef DEF_HEADER_GENERIC_ALGORITHM
#define DEF_HEADER_GENERIC_ALGORITHM

#include <GenericField.h>

void Algorithm_naive_power(Field * field, void * result, void * value, long exponent);

void Algorithm_fast_power(Field * field, void * result, void * value, long exponent);

#endif