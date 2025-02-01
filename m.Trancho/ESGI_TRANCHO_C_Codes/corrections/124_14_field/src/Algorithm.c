/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#include <Algorithm.h>

void Algorithm_naive_power(Field * field, void * result, void * value, long exponent) {
  void * used = malloc(field->size);
  if(exponent >= 0) {
    field->fill_copy(field, used, value);
  } else {
    field->fill_multiplication_inverse(field, used, value);
    exponent *= -1;
  }
  field->fill_multiplication_neutral(field, result);
  for( ; exponent > 0; --exponent) {
    field->fill_multiplication(field, result, result, used);
  }
  free(used);
}

void Algorithm_fast_power(Field * field, void * result, void * value, long exponent) {
  void * used = malloc(field->size);
  field->fill_multiplication_neutral(field, used);
  if(exponent >= 0) {
    field->fill_copy(field, used, value);
  } else {
    field->fill_multiplication_inverse(field, used, value);
    exponent *= -1;
  }
  field->fill_multiplication_neutral(field, result);
  for( ; exponent > 0; exponent >>= 1) {
    if(exponent & 1) {
      field->fill_multiplication(field, result, result, used);
    }
    field->fill_multiplication(field, used, used, used);
  }
  free(used);
}
