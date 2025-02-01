/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 124.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ReelField.h>
#include <ModularField.h>
#include <IntField.h>
#include <Algorithm.h>
#include <MatrixField.h>

#include <gmp.h>
#include <time.h>

int main() {
  clock_t start;
  clock_t end;

  Field field = ReelField();
  {
    double v = 3.;
    start = clock();
    Algorithm_fast_power(&field, &v, &v, 10);
    end = clock();
    field.display(&field, stdout, &v);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
  }

  field = ModularField(127);
  {
    unsigned int v = 42;
    start = clock();
    Algorithm_fast_power(&field, &v, &v, 125);
    end = clock();
    field.display(&field, stdout, &v);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
  }

  field = IntField();
  {
    mpz_t v;
    mpz_init_set_ui(v, 2);
    start = clock();
    Algorithm_fast_power(&field, &v, &v, 10000);
    end = clock();
    field.display(&field, stdout, &v);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
  }

  field = Matrix2x2Field(ReelField());
  {
    double v[2][2] = {
        {1., 1.},
        {1., 0.}
    };
    start = clock();
    Algorithm_fast_power(&field, v, v, 1000);
    end = clock();
    field.display(&field, stdout, v);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
  }

  field = Matrix2x2Field(IntField());
  {
    mpz_t v[2][2];
    mpz_init_set_ui(v[0][0], 1); mpz_init_set_ui(v[0][1], 1);
    mpz_init_set_ui(v[1][0], 1); mpz_init_set_ui(v[1][1], 0);
    start = clock();
    Algorithm_fast_power(&field, v, v, 20000 - 1);
    end = clock();
    field.display(&field, stdout, v);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
  }

  field = Matrix2x2Field(ModularField(127));
  {
    unsigned int v[2][2] = {
        {1, 2},
        {3, 4}
    };
    unsigned int a[2][2];
    start = clock();
    Algorithm_fast_power(&field, a, v, 42);
    Algorithm_fast_power(&field, v, v, -42);
    end = clock();
    field.display(&field, stdout, v);
    printf("\n");
    field.display(&field, stdout, a);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    field.fill_multiplication(&field, v, v, a);
    end = clock();
    field.display(&field, stdout, v);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
  }

  field = Matrix2x2Field(Matrix2x2Field(ModularField(127)));
  {
    unsigned int v[2][2][2][2] = {
        {
            {{1, 2},
             {5, 6}},
             
            {{3, 4},
             {7, 8}}
        },
        {
            {{9, 10},
             {13, 14}},
             
            {{11, 12},
             {15, 16}}
        }
    };
    start = clock();
    Algorithm_fast_power(&field, v, v, 42);
    end = clock();
    field.display(&field, stdout, v);
    printf("\n - (in %g s)\n", (double)(end - start) / CLOCKS_PER_SEC);
  }
	exit(EXIT_SUCCESS);
}