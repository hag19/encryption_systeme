#include "rsa.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global variables for RSA
mpz_t p, q, n, phi, e, d;

void initializeRSA() {
    mpz_inits(p, q, n, phi, e, d, NULL);
    srand(time(NULL)); // Seed the random number generator
}

void clearRSA() {
    mpz_clears(p, q, n, phi, e, d, NULL);
}

int isPrime(mpz_t num) {
    return mpz_probab_prime_p(num, 25);
}

void generatePrime(mpz_t prime) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, rand());
    do {
        mpz_urandomb(prime, state, MIN_PRIME_BITS);
    } while (!isPrime(prime));
    gmp_randclear(state);  
}

void gcd(mpz_t result, mpz_t a, mpz_t b) {
    mpz_gcd(result, a, b);
}

void modInverse(mpz_t result, mpz_t e, mpz_t phi) {
    mpz_invert(result, e, phi);
}

void generateKeys() {
    generatePrime(p);
    generatePrime(q);
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);

    // Find e
    mpz_set_ui(e, 65537); // Common choice for e

    // Find d
    modInverse(d, e, phi);

    // Print keys as a mix of characters and numbers
    char publicKey[MIN_PRIME_BITS / 8];
    char privateKey[MIN_PRIME_BITS / 8];
    mpz_get_str(publicKey, 62, e); // Base 62 for mix of characters and numbers
    mpz_get_str(privateKey, 62, d);

    printf("Generated public key: %s\n", publicKey);
    printf("Generated private key: %s\n", privateKey);
}

void encryptFile(const char *filePath) {
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_encrypted_file", "wb");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }

    unsigned char buffer;
    mpz_t plain, cipher;
    mpz_inits(plain, cipher, NULL);

    while (fread(&buffer, sizeof(unsigned char), 1, in)) {
        mpz_set_ui(plain, buffer);
        mpz_powm(cipher, plain, e, n);
        if (mpz_out_raw(out, cipher) == 0) {
            perror("Error writing to file");
            mpz_clears(plain, cipher, NULL);
            fclose(in);
            fclose(out);
            exit(EXIT_FAILURE);
        }
    }

    mpz_clears(plain, cipher, NULL);
    fclose(in);
    fclose(out);

    if (remove(filePath) != 0 || rename("temp_encrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

void decryptFile(const char *filePath, mpz_t key, mpz_t modulus) {
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_decrypted_file", "wb");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }

    mpz_t cipher, plain;
    mpz_inits(cipher, plain, NULL);

    while (mpz_inp_raw(cipher, in)) {
        mpz_powm(plain, cipher, key, modulus);
        unsigned char decryptedChar = (unsigned char)mpz_get_ui(plain);

        if (fwrite(&decryptedChar, sizeof(unsigned char), 1, out) != 1) {
            perror("Error writing to file");
            mpz_clears(cipher, plain, NULL);
            fclose(in);
            fclose(out);
            exit(EXIT_FAILURE);
        }
    }

    mpz_clears(cipher, plain, NULL);
    fclose(in);
    fclose(out);

    if (remove(filePath) != 0 || rename("temp_decrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

EncryptionAlgorithm rsa_algorithm = {
    .name = "RSA",
    .encrypt = encryptFile,
    .decrypt = decryptFile
};
