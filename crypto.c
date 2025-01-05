#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Helper functions for RSA
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

uint64_t mod_inverse(uint64_t a, uint64_t m) {
    uint64_t m0 = m, t, q;
    uint64_t x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

void generate_rsa_keys(uint64_t *public_key, uint64_t *private_key, uint64_t *n) {
    uint64_t p = 61, q = 53; // Two prime numbers
    *n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    *public_key = 17; // Common public exponent
    *private_key = mod_inverse(*public_key, phi);
}

uint64_t rsa_encrypt(uint64_t message, uint64_t public_key, uint64_t n) {
    return mod_exp(message, public_key, n);
}

uint64_t rsa_decrypt(uint64_t ciphertext, uint64_t private_key, uint64_t n) {
    return mod_exp(ciphertext, private_key, n);
}

// Helper functions for AES
static const uint8_t sbox[256] = {
    /* Standard AES S-box values */
};

void aes_sub_bytes(uint8_t *block) {
    for (int i = 0; i < 16; ++i) {
        block[i] = sbox[block[i]];
    }
}

void aes_shift_rows(uint8_t *block) {
    uint8_t temp;

    // Row 1
    temp = block[1];
    block[1] = block[5];
    block[5] = block[9];
    block[9] = block[13];
    block[13] = temp;

    // Row 2
    temp = block[2];
    block[2] = block[10];
    block[10] = temp;
    temp = block[6];
    block[6] = block[14];
    block[14] = temp;

    // Row 3
    temp = block[3];
    block[3] = block[15];
    block[15] = block[11];
    block[11] = block[7];
    block[7] = temp;
}

void aes_mix_columns(uint8_t *block) {
    /* MixColumns transformation */
}

void aes_add_round_key(uint8_t *block, uint8_t *round_key) {
    for (int i = 0; i < 16; ++i) {
        block[i] ^= round_key[i];
    }
}

void aes_encrypt_block(uint8_t *block, uint8_t *key) {
    aes_add_round_key(block, key);
    for (int round = 1; round < 10; ++round) {
        aes_sub_bytes(block);
        aes_shift_rows(block);
        aes_mix_columns(block);
        aes_add_round_key(block, key);
    }
    aes_sub_bytes(block);
    aes_shift_rows(block);
    aes_add_round_key(block, key);
}

void aes_decrypt_block(uint8_t *block, uint8_t *key) {
    /* Reverse of AES encryption */
}
