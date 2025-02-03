#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gmp.h"
#include "rsa.h"
#include <stdint.h>
#include "../types/constants.h"
// Global variables for RSA
 mpz_t p, q, n, phi, e, d,p1, q1,cipher, plain;
 gmp_randstate_t state;
void initializeRSA() {
    mpz_inits(p, q, n, phi, e, d,p1, q1,cipher, plain, NULL);
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
}

void clearRSA() {
    mpz_clears(p, q, n, phi, e, d,p1, q1,cipher, plain, NULL);
    gmp_randclear(state);
}

int isPrime(mpz_t num) {
    return mpz_probab_prime_p(num, 25);
}

void gcd(mpz_t result, mpz_t a, mpz_t b) {
    mpz_gcd(result, a, b);
}

void modInverse(mpz_t result, mpz_t e, mpz_t phi) {
    mpz_invert(result, e, phi);
}

void generatePrime(mpz_t prime) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL) ^ (intptr_t)&state);
    do {
        mpz_urandomb(prime, state, BUFFER_SIZE/2); // Generate 512-bit prime
        mpz_setbit(prime, 511); // Ensure 512-bit prime
    } while (!isPrime(prime));
    gmp_randclear(state);
}

void generateKeys() {
    do {
        generatePrime(p);
        generatePrime(q);
    } while (mpz_cmp(p, q) == 0);

    mpz_mul(n, p, q);
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);

    mpz_set_ui(e, 65537); // Fixed public exponent
    gcd(d, e, phi); // Check if gcd(e, phi) == 1
    if (mpz_cmp_ui(d, 1) != 0) {
        fprintf(stderr, "Error: e is not coprime with φ(n)\n");
        exit(EXIT_FAILURE);
    }
    
    // Calculate private key d = e^(-1) mod phi
    modInverse(d, e, phi);
    char *d_base62 = mpz_get_str(NULL, 62, d);
    char *n_base62 = mpz_get_str(NULL, 62, n);
    gmp_printf("Generated public key (e): %Zd\nGenerated private key (d): %s\nGenerated modulus (n): %s\n", e,d_base62,n_base62);
    free(d_base62);
    free(n_base62);
}

void encryptFile(const char *filepath) {
    FILE *in = fopen(filepath, "rb");
    FILE *out = fopen("tmp_encrypted_file", "wb+");  // Temporary encrypted file
    if (!in || !out) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    initializeRSA();
    generateKeys();
    unsigned char buffer[128];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        mpz_import(plain, bytesRead, 1, 1, 0, 0, buffer);  // Import data as mpz_t
        mpz_powm(cipher, plain, e, n);  // Encrypt the block
         char *cipher_base62 = mpz_get_str(NULL, 62, cipher);
        fprintf(out, "%s\n", cipher_base62);
        free(cipher_base62);  // Write the encrypted data to the file in hexadecimal format
    }
    fclose(in);
    fclose(out);
    printf("Encryption complete.\n");

    // After successful encryption, replace the original file with the encrypted one
    if (rename("tmp_encrypted_file", filepath) != 0) {
        perror("Error replacing original file with encrypted file");
        exit(EXIT_FAILURE);
    }
    printf("Original file replaced with encrypted version.\n");
    clearRSA();
}

void decryptFile(const char *filepath) {
    FILE *in = fopen(filepath, "rb");
    FILE *out = fopen("tmp_decrypted_file", "wb+");  // Temporary decrypted file
    if (!in || !out) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    initializeRSA();
    char cipherStr[BUFFER_SIZE], keyStr[BUFFER_SIZE], modulusStr[BUFFER_SIZE];
    printf("Enter private key (d): \n");
    scanf("%s", &keyStr);
    printf("Enter modulus (n): \n");
    scanf("%s", &modulusStr);
    mpz_set_str(d, keyStr, 62);
    mpz_set_str(n, modulusStr, 62);

    while (fgets(cipherStr, sizeof(cipherStr), in)) {
        cipherStr[strcspn(cipherStr, "\n")] = '\0'; // Remove newline

        mpz_set_str(cipher, cipherStr, 62); // Convert hex string to integer
        mpz_powm(plain, cipher, d, n); // Decrypt: m = c^d mod n

        size_t decryptedSize;
        unsigned char *decrypted_data = (unsigned char *)mpz_export(NULL, &decryptedSize, 1, 1, 0, 0, plain);
        fwrite(decrypted_data, 1, decryptedSize, out);
        free(decrypted_data);
    }
    fclose(in);
    fclose(out);
    printf("Decryption complete! Decrypted data saved in decrypted.txt\n");

    // After successful decryption, replace the original file with the decrypted one
    if (rename("tmp_decrypted_file", filepath) != 0) {
        perror("Error replacing original file with decrypted file");
        exit(EXIT_FAILURE);
    }
    printf("Original file replaced with decrypted version.\n");
    clearRSA();
}

EncryptionAlgorithm rsa_algorithm = {
    .name = "RSA",
    .encrypt = encryptFile,
    .decrypt = decryptFile
};
