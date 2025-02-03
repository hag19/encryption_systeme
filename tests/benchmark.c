#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "../src/types/encryption_algorithm.h"
#include "../src/types/constants.h"

void benchmark_algorithm(EncryptionAlgorithm *algorithm, char *filePath) {
    clock_t start, end;
    double cpu_time_used;
    printf("Benchmarking %s algorithm\n", algorithm->name);

    // Benchmark encryption
    start = clock();
    algorithm->encrypt(filePath);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%s encryption time: %f seconds\n", algorithm->name, cpu_time_used);

    // Benchmark decryption
    start = clock();
    algorithm->decrypt(filePath);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%s decryption time: %f seconds\n", algorithm->name, cpu_time_used);
}
