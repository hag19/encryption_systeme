#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "atbash.h"

void atbash_cipher(char *input, char *output) {
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            if (isupper(input[i])) {
                output[i] = 'Z' - (input[i] - 'A');
            } else {
                output[i] = 'z' - (input[i] - 'a');
            }
        } else {
            output[i] = input[i];
        }
    }
    output[i] = '\0';
}

void atbash_encrypt(const char *filepath) {
    FILE *file = fopen(filepath, "rb+");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    char *encrypted = (char *)malloc(fileSize + 1);
    if (!encrypted) {
        perror("Memory allocation error");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    atbash_cipher(buffer, encrypted);

    fseek(file, 0, SEEK_SET);
    fwrite(encrypted, 1, fileSize, file);
    fclose(file);

    free(buffer);
    free(encrypted);

    printf("Encryption complete.\n");
}

void atbash_decrypt(const char *filepath) {
    atbash_encrypt(filepath);
}

EncryptionAlgorithm atbash_algorithm = {
    .name = "ATBASH",
    .encrypt = atbash_encrypt,
    .decrypt = atbash_decrypt
};

