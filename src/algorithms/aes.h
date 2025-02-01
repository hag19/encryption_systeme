#ifndef AES_H
#define AES_H

#include <stdint.h>
#include "../types/encryption_algorithm.h"



void sub_bytes(uint8_t *state);
void inv_sub_bytes(uint8_t *state);
void shift_rows(uint8_t *state);
void inv_shift_rows(uint8_t *state);
void add_round_key(uint8_t *state, const uint8_t *round_key);
void mix_columns(uint8_t *state);
void inv_mix_columns(uint8_t *state);
void key_expansion(const uint8_t *key, uint8_t *round_keys);
void aes_encrypt(uint8_t *data, const uint8_t *round_keys);
void aes_decrypt(uint8_t *data, const uint8_t *round_keys);
void generate_key(uint8_t *key);
void print_key(const uint8_t *key);
void aes_encrypt_file(const char *filepath);
void aes_decrypt_file(const char *filepath);

extern EncryptionAlgorithm aes_algorithm;

#endif // AES_H