#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(const char filename, uint8_t **data, size_t *size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    data = malloc(size);
    fread(data, 1,size, file);
    fclose(file);
}

void write_file(const char *filename, uint8_t *data, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("File write failed");
        exit(EXIT_FAILURE);
    }

    fwrite(data, 1, size, file);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <encrypted_file> <public_key_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *encrypted_file = argv[2];
    const char *public_key_file = argv[3];

    uint64_t public_key, private_key, n;
    generate_rsa_keys(&public_key, &private_key, &n);

    printf("Public Key: %lu, N: %lu\n", public_key, n);
    printf("Private Key: %lu\n", private_key);

    uint8_t *data;
    size_t data_size;
    read_file(input_file, &data, &data_size);

    uint8_t encrypted_data[data_size];
    uint8_t aes_key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    for (size_t i = 0; i < data_size; i += 16) {
        aes_encrypt_block(data + i, aes_key);
    }

    write_file(encrypted_file, data, data_size);

    FILE *pub_key_file = fopen(public_key_file, "w");
    fprintf(pub_key_file, "Public Key: %lu, N: %lu\n", public_key, n);
    fclose(pub_key_file);

    free(data);
    return EXIT_SUCCESS;
}