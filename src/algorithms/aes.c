#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aes.h"
#include <unistd.h>
#include "../types/constants.h"
uint8_t key[AES_KEY_SIZE];
static const uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
};

static const uint8_t inv_sbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,
};
static const uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

void sub_bytes(uint8_t *state) {
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
        state[i] = sbox[state[i]];
}

void inv_sub_bytes(uint8_t *state) {
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
        state[i] = inv_sbox[state[i]];
}

void shift_rows(uint8_t *state) {
    uint8_t tmp[AES_BLOCK_SIZE];
    memcpy(tmp, state, AES_BLOCK_SIZE);
    state[1] = tmp[5]; state[5] = tmp[9]; state[9] = tmp[13]; state[13] = tmp[1];
    state[2] = tmp[10]; state[6] = tmp[14]; state[10] = tmp[2]; state[14] = tmp[6];
    state[3] = tmp[15]; state[7] = tmp[3]; state[11] = tmp[7]; state[15] = tmp[11];
}

void inv_shift_rows(uint8_t *state) {
    uint8_t tmp[AES_BLOCK_SIZE];
    memcpy(tmp, state, AES_BLOCK_SIZE);
    state[1] = tmp[13]; state[5] = tmp[1]; state[9] = tmp[5]; state[13] = tmp[9];
    state[2] = tmp[10]; state[6] = tmp[14]; state[10] = tmp[2]; state[14] = tmp[6];
    state[3] = tmp[7]; state[7] = tmp[11]; state[11] = tmp[15]; state[15] = tmp[3];
}

void add_round_key(uint8_t *state, const uint8_t *round_key) {
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
        state[i] ^= round_key[i];
}

void mix_columns(uint8_t *state) {
    uint8_t tmp[AES_BLOCK_SIZE];
    for (int i = 0; i < 4; i++) {
        tmp[4 * i] = (uint8_t) (0x02 * state[4 * i] ^ 0x03 * state[4 * i + 1] ^ state[4 * i + 2] ^ state[4 * i + 3]);
        tmp[4 * i + 1] = (uint8_t) (state[4 * i] ^ 0x02 * state[4 * i + 1] ^ 0x03 * state[4 * i + 2] ^ state[4 * i + 3]);
        tmp[4 * i + 2] = (uint8_t) (state[4 * i] ^ state[4 * i + 1] ^ 0x02 * state[4 * i + 2] ^ 0x03 * state[4 * i + 3]);
        tmp[4 * i + 3] = (uint8_t) (0x03 * state[4 * i] ^ state[4 * i + 1] ^ state[4 * i + 2] ^ 0x02 * state[4 * i + 3]);
    }
    memcpy(state, tmp, AES_BLOCK_SIZE);
}

void inv_mix_columns(uint8_t *state) {
    uint8_t tmp[AES_BLOCK_SIZE];
    for (int i = 0; i < 4; i++) {
        tmp[4 * i] = (uint8_t) (0x0e * state[4 * i] ^ 0x0b * state[4 * i + 1] ^ 0x0d * state[4 * i + 2] ^ 0x09 * state[4 * i + 3]);
        tmp[4 * i + 1] = (uint8_t) (0x09 * state[4 * i] ^ 0x0e * state[4 * i + 1] ^ 0x0b * state[4 * i + 2] ^ 0x0d * state[4 * i + 3]);
        tmp[4 * i + 2] = (uint8_t) (0x0d * state[4 * i] ^ 0x09 * state[4 * i + 1] ^ 0x0e * state[4 * i + 2] ^ 0x0b * state[4 * i + 3]);
        tmp[4 * i + 3] = (uint8_t) (0x0b * state[4 * i] ^ 0x0d * state[4 * i + 1] ^ 0x09 * state[4 * i + 2] ^ 0x0e * state[4 * i + 3]);
    }
    memcpy(state, tmp, AES_BLOCK_SIZE);
}


void key_expansion(const uint8_t *key, uint8_t *round_keys) {
    memcpy(round_keys, key, AES_KEY_SIZE);

    uint8_t temp[4];
    int i = AES_KEY_SIZE;
    int rcon_index = 0;

    while (i < (AES_ROUNDS + 1) * AES_BLOCK_SIZE) {
        memcpy(temp, round_keys + i - 4, 4);

        if (i % AES_KEY_SIZE == 0) {
            // Rotate
            uint8_t t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;

            // SubBytes
            for (int j = 0; j < 4; j++) {
                temp[j] = sbox[temp[j]];
            }

            // Rcon
            temp[0] ^= rcon[rcon_index++];
        }

        for (int j = 0; j < 4; j++) {
            round_keys[i] = round_keys[i - AES_KEY_SIZE] ^ temp[j];
            i++;
        }
    }
}

void aes_encrypt(uint8_t *data, const uint8_t *round_keys) {
    add_round_key(data, round_keys);

    for (int round = 1; round < AES_ROUNDS; round++) {
        sub_bytes(data);
        shift_rows(data);
        mix_columns(data);
        add_round_key(data, round_keys + round * AES_BLOCK_SIZE);
    }

    sub_bytes(data);
    shift_rows(data);
    add_round_key(data, round_keys + AES_ROUNDS * AES_BLOCK_SIZE);
}

void aes_decrypt(uint8_t *data, const uint8_t *round_keys) {
    add_round_key(data, round_keys + AES_ROUNDS * AES_BLOCK_SIZE);

    for (int round = AES_ROUNDS - 1; round > 0; round--) {
        inv_shift_rows(data);
        inv_sub_bytes(data);
        add_round_key(data, round_keys + round * AES_BLOCK_SIZE);
        inv_mix_columns(data);
    }

    inv_shift_rows(data);
    inv_sub_bytes(data);
    add_round_key(data, round_keys);
}

void generate_key(uint8_t *key) {
    srand(time(NULL));
    for (int i = 0; i < AES_KEY_SIZE; i++) {
        key[i] = rand() % 256;
    }
}

void save_key(const char *your_key) {
    for (int i = 0; i < AES_KEY_SIZE; i++) {
        key[i] = your_key[i];
    }
}

void print_key() {
    printf("Encryption key: ");
    for (int i = 0; i < AES_KEY_SIZE; i++) {
        printf("%02x", key[i]);
    }
    printf("\n");
}

void aes_encrypt_file(const char *filepath) {
    int choice;
    printf("do you have aes encryption key or you need one? 1 for generate 2 for enter your key\n");
    scanf("%d", &choice);
    if (choice == 1) {
        generate_key(key);
        print_key();
    } else if (choice == 2) {
        printf("Enter the encryption key (16 bytes in hex): ");
        save_key(key);
    }

    uint8_t round_keys[(AES_ROUNDS + 1) * AES_BLOCK_SIZE];
    key_expansion(key, round_keys);

    FILE *file = fopen(filepath, "rb+");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    uint8_t buffer[AES_BLOCK_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, AES_BLOCK_SIZE, file)) > 0) {
        if (bytesRead < AES_BLOCK_SIZE) {
            // PKCS7 padding
            uint8_t pad = AES_BLOCK_SIZE - bytesRead;
            memset(buffer + bytesRead, pad, pad);
        }
        aes_encrypt(buffer, round_keys);
        fseek(file, -bytesRead, SEEK_CUR);
        fwrite(buffer, 1, AES_BLOCK_SIZE, file);
    }
    fclose(file);
    printf("Encryption complete.\n");
}

void aes_decrypt_file(const char *filepath) {
    uint8_t key[AES_KEY_SIZE];
    printf("Enter the decryption key (16 bytes in hex): ");
    for (int i = 0; i < AES_KEY_SIZE; i++) {
        unsigned int byte;
        if (scanf("%2x", &byte) != 1) {
            fprintf(stderr, "Invalid key input.\n");
            exit(EXIT_FAILURE);
        }
        key[i] = (uint8_t)byte;
    }

    uint8_t round_keys[(AES_ROUNDS + 1) * AES_BLOCK_SIZE];
    key_expansion(key, round_keys);

    FILE *file = fopen(filepath, "rb+");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    uint8_t buffer[AES_BLOCK_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, AES_BLOCK_SIZE, file)) > 0) {
        aes_decrypt(buffer, round_keys);
        fseek(file, -AES_BLOCK_SIZE, SEEK_CUR);
        fwrite(buffer, 1, AES_BLOCK_SIZE, file);
    }

    // Remove padding
    fseek(file, -AES_BLOCK_SIZE, SEEK_END);
    fread(buffer, 1, AES_BLOCK_SIZE, file);
    uint8_t pad = buffer[AES_BLOCK_SIZE - 1];
    if (pad <= AES_BLOCK_SIZE) {
        fseek(file, -pad, SEEK_END);
        long fileSize = ftell(file);
        ftruncate(fileno(file), fileSize);
    }

    fclose(file);
    printf("Decryption complete.\n");
}

EncryptionAlgorithm aes_algorithm = {
    .name = "AES",
    .encrypt = aes_encrypt_file,
    .decrypt = aes_decrypt_file
};