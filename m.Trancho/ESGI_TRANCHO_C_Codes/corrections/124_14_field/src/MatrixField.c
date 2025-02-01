/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#include <MatrixField.h>

#include <stdio.h>

void Matrix2x2Field_fill_addition_neutral(Field * field, void * value) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cvalue = (unsigned char *)value;
  int i;
  for(i = 0; i < 4; ++i) {
    subfield->fill_addition_neutral(subfield, (cvalue + i * subfield->size));
  }
}

void Matrix2x2Field_fill_multiplication_neutral(Field * field, void * value) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cvalue = (unsigned char *)value;
  subfield->fill_multiplication_neutral(subfield, (cvalue + 0 * subfield->size));
  subfield->fill_addition_neutral(subfield, (cvalue + 1 * subfield->size));
  subfield->fill_addition_neutral(subfield, (cvalue + 2 * subfield->size));
  subfield->fill_multiplication_neutral(subfield, (cvalue + 3 * subfield->size));
}

void Matrix2x2Field_fill_addition(Field * field, void * result, void * first, void * second) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cresult = (unsigned char *)result;
  unsigned char * cfirst = (unsigned char *)first;
  unsigned char * csecond = (unsigned char *)second;
  int i;
  for(i = 0; i < 4; ++i) {
    subfield->fill_addition(subfield, (cresult + i * subfield->size), (cfirst + i * subfield->size), (csecond + i * subfield->size));
  }
}

void Matrix2x2Field_fill_multiplication(Field * field, void * result, void * first, void * second) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cfirst = (unsigned char *)first;
  unsigned char * csecond = (unsigned char *)second;
  int i, l, c;
  void * tmp = malloc(subfield->size);
  void * aux = malloc(field->size);
  unsigned char * caux = (unsigned char *)aux;
  subfield->fill_addition_neutral(subfield, tmp);
  for(l = 0; l < 2; ++l) {
    for(c = 0; c < 2; ++c) {
      subfield->fill_addition_neutral(subfield, (caux + (l * 2 + c) * subfield->size));
      for(i = 0; i < 2; ++i) {
        subfield->fill_multiplication(subfield, tmp, (cfirst + (l * 2 + i) * subfield->size), (csecond + (i * 2 + c) * subfield->size));
        subfield->fill_addition(subfield, (caux + (l * 2 + c) * subfield->size), (caux + (l * 2 + c) * subfield->size), tmp);
      }
    }
  }
  field->fill_copy(field, result, aux);
  free(aux);
  free(tmp);
}

void Matrix2x2Field_fill_copy(Field * field, void * result, void * value) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cresult = (unsigned char *)result;
  unsigned char * cvalue = (unsigned char *)value;
  int i;
  for(i = 0; i < 4; ++i) {
    subfield->fill_copy(subfield, (cresult + i * subfield->size), (cvalue + i * subfield->size));
  }
}

void Matrix2x2Field_fill_addition_inverse(Field * field, void * result, void * value) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cresult = (unsigned char *)result;
  unsigned char * cvalue = (unsigned char *)value;
  int i;
  for(i = 0; i < 4; ++i) {
    subfield->fill_addition_inverse(subfield, (cresult + i * subfield->size), (cvalue + i * subfield->size));
  }
}

void Matrix2x2Field_fill_multiplication_inverse(Field * field, void * result, void * value) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cresult = (unsigned char *)result;
  unsigned char * cvalue = (unsigned char *)value;
  void * determinant = malloc(subfield->size);
  void * tmp = malloc(subfield->size);
  subfield->fill_multiplication(subfield, determinant, (cvalue + 0 * subfield->size), (cvalue + 3 * subfield->size));
  subfield->fill_multiplication(subfield, tmp, (cvalue + 1 * subfield->size), (cvalue + 2 * subfield->size));
  subfield->fill_addition_inverse(subfield, tmp, tmp);
  subfield->fill_addition(subfield, tmp, determinant, tmp);
  subfield->fill_multiplication_inverse(subfield, determinant, tmp);
  subfield->fill_copy(subfield, tmp, (cvalue + 3 * subfield->size));
  subfield->fill_copy(subfield, (cresult + 3 * subfield->size), (cvalue + 0 * subfield->size));
  subfield->fill_copy(subfield, (cresult + 0 * subfield->size), tmp);
  subfield->fill_addition_inverse(subfield, (cresult + 1 * subfield->size), (cvalue + 1 * subfield->size));
  subfield->fill_addition_inverse(subfield, (cresult + 2 * subfield->size), (cvalue + 2 * subfield->size));
  int i;
  for(i = 0; i < 4; ++i) {
    subfield->fill_multiplication(subfield, (cresult + i * subfield->size), (cresult + i * subfield->size), determinant);
  }
  free(determinant);
  free(tmp);
}

size_t Matrix2x2Field_display(Field * field, FILE * ostream, void * value) {
  Field * subfield = ((Field *)(field->userData));
  unsigned char * cvalue = (unsigned char *)value;
  size_t count = 0;
  count += fprintf(ostream, "{{");
  count += subfield->display(subfield, ostream, (cvalue + 0 * subfield->size));
  count += fprintf(ostream, ", ");
  count += subfield->display(subfield, ostream, (cvalue + 1 * subfield->size));
  count += fprintf(ostream, "}, {");
  count += subfield->display(subfield, ostream, (cvalue + 2 * subfield->size));
  count += fprintf(ostream, ", ");
  count += subfield->display(subfield, ostream, (cvalue + 3 * subfield->size));
  count += fprintf(ostream, "}}");
  return count;
}

Field Matrix2x2Field(Field subfield) {
  Field field;
  field.size = subfield.size * 4;
  field.fill_addition_neutral = Matrix2x2Field_fill_addition_neutral;
  field.fill_multiplication_neutral = Matrix2x2Field_fill_multiplication_neutral;
  field.fill_addition = Matrix2x2Field_fill_addition;
  field.fill_multiplication = Matrix2x2Field_fill_multiplication;
  field.fill_copy = Matrix2x2Field_fill_copy;
  field.fill_addition_inverse = Matrix2x2Field_fill_addition_inverse;
  field.fill_multiplication_inverse = Matrix2x2Field_fill_multiplication_inverse;
  field.display = Matrix2x2Field_display;
  field.userData = malloc(sizeof(Field));
  *((Field *)(field.userData)) = subfield;
  return field;
}
