#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>
#include <stddef.h>
// RSA functions
void generate_rsa_keys(uint64_t public_key, uint64_t *private_key, uint64_t n);
uint64_t rsa_encrypt(uint64_t message, uint64_t *public_key, uint64_t n);
uint64_t rsa_decrypt(uint64_t ciphertext, uint64_t *private_key, uint64_t n);

// AES functions
void aes_encrypt_block(uint8_t block, uint8_t key);
void aes_decrypt_block(uint8_t block, uint8_t *key);

#endif // CRYPTO_H