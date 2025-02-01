/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#include <IntField.h>

#include <stdio.h>
#include <gmp.h>

void IntField_fill_addition_neutral(Field * field, mpz_t * value) {
  mpz_init_set_ui(*value, 0);
}

void IntField_fill_multiplication_neutral(Field * field, mpz_t * value) {
  mpz_init_set_ui(*value, 1);
}

void IntField_fill_addition(Field * field, mpz_t * result, mpz_t * first, mpz_t * second) {
  mpz_add(*result, *first, *second);
}

void IntField_fill_multiplication(Field * field, mpz_t * result, mpz_t * first, mpz_t * second) {
  mpz_mul(*result, *first, *second);
}

void IntField_fill_copy(Field * field, mpz_t * result, mpz_t * value) {
  mpz_set(*result, *value);
}

void IntField_fill_addition_inverse(Field * field, mpz_t * result, mpz_t * value) {
  mpz_mul_si(*result, *value, -1);
}

void IntField_fill_multiplication_inverse(Field * field, mpz_t * result, mpz_t * value) {
  if(mpz_cmpabs_ui(*value, 1)) {
    mpz_init_set_ui(*result, 1);
  } else {
    mpz_init_set_ui(*result, 0);
  }
}

size_t IntField_display(Field * field, FILE * ostream, mpz_t * value) {
  return mpz_out_str(ostream, 10, *value);
}

Field IntField() {
  Field field;
  field.size = sizeof(mpz_t);
  field.fill_addition_neutral = (void (*)(Field *, void *))IntField_fill_addition_neutral;
  field.fill_multiplication_neutral = (void (*)(Field *, void *))IntField_fill_multiplication_neutral;
  field.fill_addition = (void (*)(Field *, void *, void *, void *))IntField_fill_addition;
  field.fill_multiplication = (void (*)(Field *, void *, void *, void *))IntField_fill_multiplication;
  field.fill_copy = (void (*)(Field *, void *, void *))IntField_fill_copy;
  field.fill_addition_inverse = (void (*)(Field *, void *, void *))IntField_fill_addition_inverse;
  field.fill_multiplication_inverse = (void (*)(Field *, void *, void *))IntField_fill_multiplication_inverse;
  field.display = (size_t (*)(Field *, FILE *, void *))IntField_display;
  field.userData = NULL;
  return field;
}
