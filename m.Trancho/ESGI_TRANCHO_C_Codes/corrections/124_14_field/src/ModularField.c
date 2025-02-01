/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#include <ModularField.h>

#include <stdio.h>

void ModularField_fill_addition_neutral(Field * field, unsigned int * value) {
  *value = 0;
}

void ModularField_fill_multiplication_neutral(Field * field, unsigned int * value) {
  *value = 1;
}

void ModularField_fill_addition(Field * field, unsigned int * result, unsigned int * first, unsigned int * second) {
  *result = (*first + *second) % *((unsigned int *)(field->userData));
}

void ModularField_fill_multiplication(Field * field, unsigned int * result, unsigned int * first, unsigned int * second) {
  *result = (*first * *second) % *((unsigned int *)(field->userData));
}

void ModularField_fill_copy(Field * field, unsigned int * result, unsigned int * value) {
  *result = *value;
}

void ModularField_fill_addition_inverse(Field * field, unsigned int * result, unsigned int * value) {
  *result = (-*value + *((unsigned int *)(field->userData))) % *((unsigned int *)(field->userData));
}

void ModularField_fill_multiplication_inverse(Field * field, unsigned int * result, unsigned int * value) {
  long u0 = 1, v0 = 0;
  long u1 = 0, v1 = 1;
  long r0, r1;
  long tmp;
  r0 = *((unsigned int *)(field->userData));
  r1 = *value;
  long q;
  while(r1 != 0) {
    q = r0 / r1;
    tmp = r1;
    r1 = r0 - q * r1;
    r0 = tmp;
    tmp = u1;
    u1 = u0 - q * u1;
    u0 = tmp;
    tmp = v1;
    v1 = v0 - q * v1;
    v0 = tmp;
  }
  *result = (unsigned int)(v0 + *((unsigned int *)(field->userData))) % *((unsigned int *)(field->userData));
}

size_t ModularField_display(Field * field, FILE * ostream, unsigned int * value) {
  return fprintf(ostream, "%u [%u]", *value, *((unsigned int *)(field->userData)));
}

Field ModularField(unsigned int p) {
  Field field;
  field.size = sizeof(unsigned int);
  field.fill_addition_neutral = (void (*)(Field *, void *))ModularField_fill_addition_neutral;
  field.fill_multiplication_neutral = (void (*)(Field *, void *))ModularField_fill_multiplication_neutral;
  field.fill_addition = (void (*)(Field *, void *, void *, void *))ModularField_fill_addition;
  field.fill_multiplication = (void (*)(Field *, void *, void *, void *))ModularField_fill_multiplication;
  field.fill_copy = (void (*)(Field *, void *, void *))ModularField_fill_copy;
  field.fill_addition_inverse = (void (*)(Field *, void *, void *))ModularField_fill_addition_inverse;
  field.fill_multiplication_inverse = (void (*)(Field *, void *, void *))ModularField_fill_multiplication_inverse;
  field.display = (size_t (*)(Field *, FILE *, void *))ModularField_display;
  field.userData = malloc(sizeof(unsigned int));
  *((unsigned int *)(field.userData)) = p;
  return field;
}
