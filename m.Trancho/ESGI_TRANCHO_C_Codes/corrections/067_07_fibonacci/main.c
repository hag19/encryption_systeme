/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 67.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Fonction récursive naïve pour calculer la suite de          */
/* Fibonacci depuis sa définition :                            */
unsigned long fibo_rec(int n) {
  if(n <= 1) {
    return n;
  }
  return fibo_rec(n - 1) + fibo_rec(n - 2);
}

/* Version itérative du calcul de la suite de Fibonacci : */
unsigned long fibo_lin(int n) {
  unsigned long u0 = 0, u1 = 1, r;
  while(n-- > 0) {
    r = u1;
    u1 = u1 + u0;
    u0 = r;
  }
  return u0;
}

/* Affectation d'une matrice depuis ses coefficients : */
void matrix2x2_set(unsigned long matrix[2][2],
  unsigned long a, unsigned long b,
  unsigned long c, unsigned long d) {
  
  matrix[0][0] = a; matrix[0][1] = b;
  matrix[1][0] = c; matrix[1][1] = d;
}

/* Affectation d'un vecteur depuis ses coefficients : */
void vector2_set(unsigned long vector[2],
  unsigned long a, unsigned long b) {
  
  vector[0] = a;
  vector[1] = b;
}

/* Multiplication matrice * vecteur */
void matrix2x2_mul_vector2(
  unsigned long res[2],
  unsigned long first[2][2],
  unsigned long second[2]) {
  
  unsigned long x = second[0], y = second[1];
  
  res[0] = first[0][0] * x + first[0][1] * y;
  res[1] = first[1][0] * x + first[1][1] * y;
}

/* Copie d'une matrice pour affectation : */
void matrix2x2_copy(
  unsigned long dest[2][2],
  unsigned long src[2][2]) {
  
  int i, j;
  for(i = 0; i < 2; ++i) {
    for(j = 0; j < 2; ++j) {
      dest[i][j] = src[i][j];
    }
  }
}

/* Multiplication matrice * matrice : */
void matrix2x2_mul_matrix2x2(
  unsigned long res[2][2],
  unsigned long first[2][2],
  unsigned long second[2][2]) {
  
  unsigned long a = first[0][0], b = first[0][1];
  unsigned long c = first[1][0], d = first[1][1];
  
  unsigned long x = second[0][0], z = second[0][1];
  unsigned long y = second[1][0], w = second[1][1];
  
  res[0][0] = a * x + b * y; res[0][1] = a * z + b * w;
  res[1][0] = c * x + d * y; res[1][1] = c * z + d * w;
}

void matrix2x2_display(unsigned long matrix[2][2]) {
  printf("Matrix2x2 :\n");
  int i, j;
  for(i = 0; i < 2; ++i) {
    if(i != 0) {
      printf("\n");
    }
    for(j = 0; j < 2; ++j) {
      if(j != 0) {
        printf(" ");
      }
      printf("%18lu", matrix[i][j]);
    }
  }
}

/* Fonction puissance d'une matrice (complexité linéaire) : */
void matrix2x2_power_naive(
  unsigned long res[2][2],
  unsigned long matrix[2][2],
  int n) {
  
  unsigned long tmp[2][2];
  /* tmp = 1 (identité matrice) */
  matrix2x2_set(tmp,
    1, 0,
    0, 1);
  while(n-- > 0) {
    /* tmp = tmp * matrix */
    matrix2x2_mul_matrix2x2(tmp, tmp, matrix);
  }
  /* res = tmp */
  matrix2x2_copy(res, tmp);
}

/* Fonction puissance rapide d'une matrice (complexité         */
/* logarithmique) :                                            */
void matrix2x2_power_fast(
  unsigned long res[2][2],
  unsigned long matrix[2][2],
  int n) {
  
  unsigned long tmp[2][2];
  unsigned long val[2][2];
  /* tmp = 1 (identité matrice) */
  matrix2x2_set(tmp,
    1, 0,
    0, 1);
  /* val = matrix */
  matrix2x2_copy(val, matrix);
  while(n > 0) {
    if(n % 2 == 1) {
      /* tmp = tmp * val */
      matrix2x2_mul_matrix2x2(tmp, tmp, val);
    }
    /* val = val * val */
    matrix2x2_mul_matrix2x2(val, val, val);
    n /= 2;
  }
  /* res = tmp */
  matrix2x2_copy(res, tmp);
}

/* Calcul de la suite de Fibonacci depuis la méthode proposée  */
/* avec une matrice 2x2 :                                      */
unsigned long fibo_matrix(int n) {
  unsigned long matrix[2][2];
  unsigned long vector[2];
  matrix2x2_set(matrix,
    1, 1,
    1, 0);
  vector2_set(vector,
    1, 0);
  matrix2x2_power_fast(matrix, matrix, n);
  matrix2x2_mul_vector2(vector, matrix, vector);
  return vector[1];
}

int main() {
  int n;
  printf("Entrez la valeur de l\'indice à calculer : ");
  scanf("%d", &n);
  unsigned long res;
  clock_t start, end;
  start = clock();
  res = fibo_matrix(n);
  end = clock();
  printf("fibo_matrix(%d) = %lu (%g s)\n", n, res, 
    (double)(end - start) / CLOCKS_PER_SEC);
  start = clock();
  res = fibo_lin(n);
  end = clock();
  printf("fibo_lin(%d)    = %lu (%g s)\n", n, res, 
    (double)(end - start) / CLOCKS_PER_SEC);
  if(n <= 50) {
    start = clock();
    res = fibo_rec(n);
    end = clock();
    printf("fibo_rec(%d)    = %lu (%g s)\n", n, res, 
      (double)(end - start) / CLOCKS_PER_SEC);
  } else {
    printf("fibo_rec(%d)    = ? (trop long)\n", n);
  }
  exit(EXIT_SUCCESS);
}