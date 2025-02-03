#include "diffie_hellman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gmp.h>
#include "../types/constants.h"

mpz_t dh_p, dh_g, dh_a, dh_A, dh_b, dh_B, shared_secret;

void initializeDiffieHellman() {
    mpz_inits(dh_p, dh_g, dh_a, dh_A, dh_b, dh_B, shared_secret, NULL);
    srand(time(NULL)); // Seed the random number generator
}

void clearDiffieHellman() {
    mpz_clears(dh_p, dh_g, dh_a, dh_A, dh_b, dh_B, shared_secret, NULL);
}

void generateDiffieHellmanKeys() {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, rand());

    // Generate prime dh_p
    mpz_urandomb(dh_p, state, MIN_PRIME_BITS);
    mpz_nextprime(dh_p, dh_p);

    // Generate generator dh_g
    mpz_set_ui(dh_g, 2);

    // Generate private key dh_a
    mpz_urandomm(dh_a, state, dh_p);

    // Compute public key dh_A = dh_g^dh_a mod dh_p
    mpz_powm(dh_A, dh_g, dh_a, dh_p);

    // Generate private key dh_b
    mpz_urandomm(dh_b, state, dh_p);

    // Compute public key dh_B = dh_g^dh_b mod dh_p
    mpz_powm(dh_B, dh_g, dh_b, dh_p);

    char *dh_A_base62 = mpz_get_str(NULL, 62, dh_A);
    char *dh_B_base62 = mpz_get_str(NULL, 62, dh_B);

    printf("Generated public key A: %s\n", dh_A_base62);
    printf("Generated public key B: %s\n", dh_B_base62);

    free(dh_A_base62);
    free(dh_B_base62);

    gmp_randclear(state);
}

void computeSharedSecret() {
    // Compute shared secret s = dh_B^dh_a mod dh_p
    mpz_powm(shared_secret, dh_B, dh_a, dh_p);
    char *shared_secret_base62 = mpz_get_str(NULL, 62, shared_secret);
    printf("Computed shared secret: %s\n", shared_secret_base62);
    free(shared_secret_base62);
}

void encryptDiffieHellmanFile(const char *filePath) {
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_encrypted_file", "wb+");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }

    generateDiffieHellmanKeys();
    computeSharedSecret();

    unsigned char buffer;
    mpz_t plain, cipher;
    mpz_inits(plain, cipher, NULL);

    while (fread(&buffer, sizeof(unsigned char), 1, in)) {
        mpz_set_ui(plain, buffer);
        mpz_add(cipher, plain, shared_secret); // Simple addition for encryption
        mpz_mod(cipher, cipher, dh_p);

        char *cipher_base62 = mpz_get_str(NULL, 62, cipher);
        fprintf(out, "%s\n", cipher_base62);
        free(cipher_base62);
    }

    mpz_clears(plain, cipher, NULL);
    fclose(in);
    fclose(out);

    if (remove(filePath) != 0 || rename("temp_encrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

void decryptDiffieHellmanFile(const char *filePath) {
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_decrypted_file", "wb+");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }

    initializeDiffieHellman();
    char keyStr[BUFFER_SIZE], pStr[BUFFER_SIZE];
    printf("Enter private key (a): \n");
    scanf("%s", keyStr);
    printf("Enter prime (dh_p): \n");
    scanf("%s", pStr);
    mpz_set_str(dh_a, keyStr, 62);
    mpz_set_str(dh_p, pStr, 62);

    // Compute shared secret
    computeSharedSecret();

    mpz_t cipher, plain;
    mpz_inits(cipher, plain, NULL);

    char cipher_base62[BUFFER_SIZE];
    while (fgets(cipher_base62, sizeof(cipher_base62), in)) {
        cipher_base62[strcspn(cipher_base62, "\n")] = '\0'; // Remove newline
        mpz_set_str(cipher, cipher_base62, 62);

        mpz_sub(plain, cipher, shared_secret); // Simple subtraction for decryption
        mpz_mod(plain, plain, dh_p);

        unsigned char decryptedChar = (unsigned char)mpz_get_ui(plain);
        fwrite(&decryptedChar, sizeof(unsigned char), 1, out);
    }

    mpz_clears(cipher, plain, NULL);
    fclose(in);
    fclose(out);

    if (remove(filePath) != 0 || rename("temp_decrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

EncryptionAlgorithm diffie_hellman_algorithm = {
    .name = "Diffie-Hellman",
    .encrypt = encryptDiffieHellmanFile,
    .decrypt = decryptDiffieHellmanFile
};
