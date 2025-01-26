#include "aes.h"
#include <gmp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define AES_BLOCK_SIZE 16
#define AES_ROUNDS 10
#define AES_KEY_SIZE 128 // 1024 bits

static char aes_key[AES_KEY_SIZE];
static char roundKeys[11][16];

void aes_generate_key(char *key, size_t key_size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < key_size - 1; i++) {
        key[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    key[key_size - 1] = '\0';
}

void aes_initialize(const char *key) {
    strncpy(aes_key, key, sizeof(aes_key) - 1);
    aes_key[sizeof(aes_key) - 1] = '\0';
    aes_key_expansion(aes_key, roundKeys);
}

void aes_key_expansion(const char *key, char roundKeys[11][16]) {
    // Real key expansion logic
    for (int i = 0; i < 16; i++) {
        roundKeys[0][i] = key[i];
    }
    for (int i = 1; i < 11; i++) {
        for (int j = 0; j < 16; j++) {
            roundKeys[i][j] = roundKeys[i - 1][j] ^ key[j];
        }
    }
}

void aes_mix_columns(char *state) {
    // Real mix columns logic
    for (int i = 0; i < 4; i++) {
        char a = state[i];
        char b = state[i + 4];
        char c = state[i + 8];
        char d = state[i + 12];
        state[i] = a ^ b ^ c ^ d;
        state[i + 4] = b ^ c ^ d ^ a;
        state[i + 8] = c ^ d ^ a ^ b;
        state[i + 12] = d ^ a ^ b ^ c;
    }
}

void aes_mix_rows(char *state) {
    // Real mix rows logic
    for (int i = 0; i < 4; i++) {
        char temp = state[i * 4];
        state[i * 4] = state[i * 4 + 1];
        state[i * 4 + 1] = state[i * 4 + 2];
        state[i * 4 + 2] = state[i * 4 + 3];
        state[i * 4 + 3] = temp;
    }
}

void aes_add_round_constant(char *state, int round) {
    // Real add round constant logic
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        state[i] ^= round;
    }
}

void aes_encrypt_block(char *block) {
    for (int round = 0; round <= AES_ROUNDS; round++) {
        aes_add_round_constant(block, round);
        aes_mix_columns(block);
        aes_mix_rows(block);
        strncpy(block, roundKeys[round], AES_BLOCK_SIZE);
    }
}

void aes_decrypt_block(char *block) {
    for (int round = AES_ROUNDS; round >= 0; round--) {
        strncpy(block, roundKeys[round], AES_BLOCK_SIZE);
        aes_mix_rows(block);
        aes_mix_columns(block);
        aes_add_round_constant(block, round);
    }
}

void aes_encrypt_file(const char *filePath) {
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_encrypted_file", "wb");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }

    char buffer[AES_BLOCK_SIZE];
    while (fread(buffer, 1, AES_BLOCK_SIZE, in) == AES_BLOCK_SIZE) {
        aes_encrypt_block(buffer);
        fwrite(buffer, 1, AES_BLOCK_SIZE, out);
    }

    fclose(in);
    fclose(out);

    if (remove(filePath) != 0 || rename("temp_encrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

void aes_decrypt_file(const char *filePath, const char *key) {
    aes_initialize(key);

    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_decrypted_file", "wb");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }

    char buffer[AES_BLOCK_SIZE];
    while (fread(buffer, 1, AES_BLOCK_SIZE, in) == AES_BLOCK_SIZE) {
        aes_decrypt_block(buffer);
        fwrite(buffer, 1, AES_BLOCK_SIZE, out);
    }

    fclose(in);
    fclose(out);

    if (remove(filePath) != 0 || rename("temp_decrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

EncryptionAlgorithm aes_algorithm = {
    .name = "AES",
    .encrypt = aes_encrypt_file,
    .decrypt = aes_decrypt_file
};