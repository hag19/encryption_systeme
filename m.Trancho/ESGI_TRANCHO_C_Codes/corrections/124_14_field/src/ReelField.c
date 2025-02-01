/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#include <ReelField.h>

#include <stdio.h>

void ReelField_fill_addition_neutral(Field * field, double * value) {
  *value = 0.;
}

void ReelField_fill_multiplication_neutral(Field * field, double * value) {
  *value = 1.;
}

void ReelField_fill_addition(Field * field, double * result, double * first, double * second) {
  *result = *first + *second;
}

void ReelField_fill_multiplication(Field * field, double * result, double * first, double * second) {
  *result = *first * *second;
}

void ReelField_fill_copy(Field * field, double * result, double * value) {
  *result = *value;
}

void ReelField_fill_addition_inverse(Field * field, double * result, double * value) {
  *result = -*value;
}

void ReelField_fill_multiplication_inverse(Field * field, double * result, double * value) {
  *result = 1. / *value;
}

size_t ReelField_display(Field * field, FILE * ostream, double * value) {
  return fprintf(ostream, "%g", *value);
}

Field ReelField() {
  Field field;
  field.size = sizeof(double);
  field.fill_addition_neutral = (void (*)(Field *, void *))ReelField_fill_addition_neutral;
  field.fill_multiplication_neutral = (void (*)(Field *, void *))ReelField_fill_multiplication_neutral;
  field.fill_addition = (void (*)(Field *, void *, void *, void *))ReelField_fill_addition;
  field.fill_multiplication = (void (*)(Field *, void *, void *, void *))ReelField_fill_multiplication;
  field.fill_copy = (void (*)(Field *, void *, void *))ReelField_fill_copy;
  field.fill_addition_inverse = (void (*)(Field *, void *, void *))ReelField_fill_addition_inverse;
  field.fill_multiplication_inverse = (void (*)(Field *, void *, void *))ReelField_fill_multiplication_inverse;
  field.display = (size_t (*)(Field *, FILE *, void *))ReelField_display;
  field.userData = NULL;
  return field;
}
