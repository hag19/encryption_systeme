#ifndef AES_H
#define AES_H

#include "../types/encryption_algorithm.h"

void aes_generate_key(char *key, size_t key_size);
void aes_initialize(const char *key);
void aes_encrypt(const char *input, char *output);
void aes_decrypt(const char *input, char *output);
void aes_encrypt_file(const char *filePath);
void aes_decrypt_file(const char *filePath, const char *key);

void aes_key_expansion(const char *key, char roundKeys[11][16]);
void aes_mix_columns(char *state);
void aes_mix_rows(char *state);
void aes_add_round_constant(char *state, int round);

extern EncryptionAlgorithm aes_algorithm;

#endif // AES_H