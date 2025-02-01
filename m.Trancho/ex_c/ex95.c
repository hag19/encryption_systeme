#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TERMS 100

// Iterative function to calculate generalized Fibonacci sequence without memoization
long long iterative_generalized_fibonacci(int degree, int n);
// Function to generate the first 20 terms of the sequence using the iterative approach
void generate_sequence_iterative(int degree, int n);
// Recursive function to generate the first n terms of the sequence with pointer and memoization
int generate(int degree, int n, int *sequence);
void multiply_matrix(long long *a, long long *b, long long *c, int degree);
void power_matrix(long long *a, long long *b, int degree, int n);
void generate_sequence_matrix(int degree, int n);

int main() {
    int d, n;
    printf("Enter the degree of the sequence and the number of terms: ");
    scanf("%d %d", &d, &n);
    if(d < 2) {
        printf("Degree must be greater than 1\n");
        return 1;
    }
    if(n < 1) {
        printf("Number of terms must be greater than 0\n");
        return 1;
    }
    if(n > MAX_TERMS) {
        printf("Number of terms must be less than or equal to %d\n", MAX_TERMS);
        return 1;
    }

    int *sequence = (int *)malloc(n * sizeof(int));
    clock_t start, end;
    double cpu_time_used;

    // Measure time for generate_sequence_iterative
    start = clock();
    generate_sequence_iterative(d, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for generate_sequence_iterative: %f seconds\n", cpu_time_used);

    // Measure time for generate
    start = clock();
    for (int i = 0; i < n; i++) {
        sequence[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", generate(d, i, sequence));
    }
    printf("\n");
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for generate: %f seconds\n", cpu_time_used);

    // Measure time for generate_sequence_matrix
    start = clock();
    generate_sequence_matrix(d, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for generate_sequence_matrix: %f seconds\n", cpu_time_used);

    free(sequence);
    return 0;
}

long long iterative_generalized_fibonacci(int degree, int n) {
    if (n < degree - 1) {
        return 0;
    }
    if (n == degree - 1) {
        return 1;
    }
    long long result = 0;
    for (int i = 1; i <= degree; i++) {
        result += iterative_generalized_fibonacci(degree, n - i);
    }
    return result;
}

int generate(int degree, int n, int *sequence) {
    if (n < degree - 1) {
        return 0;
    } else if (n == degree - 1) {
        return 1;
    } else {
        if (sequence[n] != -1) {
            return sequence[n];
        }
        sequence[n] = 0;
        for (int j = 1; j <= degree; j++) {
            sequence[n] += generate(degree, n - j, sequence);
        }
        return sequence[n];
    }
}

void generate_sequence_iterative(int degree, int n) {
    if(n > MAX_TERMS) {
        n = MAX_TERMS;
    }
    printf("Degree of the sequence: %d\n", degree);
    for (int i = 0; i < n; i++) {
        printf("%lld ", iterative_generalized_fibonacci(degree, i));
    }
    printf("\n");
}

void multiply_matrix(long long *a, long long *b, long long *c, int degree) {
    for(int i = 0; i < degree; i++) {
        for(int j = 0; j < degree; j++) {
            c[i * degree + j] = 0;
            for(int k = 0; k < degree; k++) {
                c[i * degree + j] += a[i * degree + k] * b[k * degree + j];
            }
        }
    }
}

void power_matrix(long long *a, long long *b, int degree, int n) {
    if(n == 1) {
        for(int i = 0; i < degree * degree; i++) {
            b[i] = a[i];
        }
        return;
    }
    long long *temp = (long long *)malloc(degree * degree * sizeof(long long));
    power_matrix(a, temp, degree, n / 2);
    if(n % 2 == 0) {
        multiply_matrix(temp, temp, b, degree);
    } else {
        long long *temp2 = (long long *)malloc(degree * degree * sizeof(long long));
        multiply_matrix(temp, temp, temp2, degree);
        multiply_matrix(temp2, a, b, degree);
        free(temp2);
    }
    free(temp);
}

void generate_sequence_matrix(int degree, int n) {
    if(n > MAX_TERMS) {
        n = MAX_TERMS;
    }
    long long *a = (long long *)malloc(degree * degree * sizeof(long long));
    long long *b = (long long *)malloc(degree * degree * sizeof(long long));

    // Initialize the transformation matrix `a`
    for (int i = 0; i < degree; i++) {
        for (int j = 0; j < degree; j++) {
            if (i == degree - 1) {
                a[i * degree + j] = 1;
            } else if (j == i + 1) {
                a[i * degree + j] = 1;
            } else {
                a[i * degree + j] = 0;
            }
        }
    }

    // Initialize the identity matrix `b`
    for (int i = 0; i < degree; i++) {
        for (int j = 0; j < degree; j++) {
            if (i == j) {
                b[i * degree + j] = 1;
            } else {
                b[i * degree + j] = 0;
            }
        }
    }

    // Print the first `n` terms of the sequence
    for (int i = 0; i < n; i++) {
        power_matrix(a, b, degree, i + 1);
        long long result = 0;
        for (int j = 0; j < degree; j++) {
            result += b[(degree - 1) * degree + j];
        }
        printf("%lld ", result);
    }
    printf("\n");

    free(a);
    free(b);
}