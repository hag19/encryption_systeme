#include "elgamal.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/constants.h"
#include "key_handeling.h"


mpz_t p_el, g, y, x, k,a, b, m,s;

void initializeElGamal() {
    mpz_inits(k, p_el, g, y, x,a, b, m,s, NULL);
}

void clearElGamal() {
    mpz_clears(p_el, g, y, x,a, b, m,s, NULL);
}
void elGamalStore(FILE *keyFile) {
    // Write public key (e), private key (d), and modulus (n) to the file
    char *p_base62 = mpz_get_str(NULL, 62, p_el);
    char *x_base62 = mpz_get_str(NULL, 62, x);
    char *y_base62 = mpz_get_str(NULL, 62, y);

    fprintf(keyFile, "p=%s\n", p_base62);
    fprintf(keyFile, "g=%Zd\n", g);
    fprintf(keyFile, "y=%s\n", y_base62);
    fprintf(keyFile, "x=%s\n", x_base62);
    gmp_printf("Generated public key (p, g, y): (%s, %Zd, %s)\nGenerated private key (x): (%s)\n", p_base62, g, y_base62,x_base62);
    free(p_base62);
    free(x_base62);
    free(y_base62);

}

// Function to load keys from a .key file
void elGamalLoad(FILE *keyFile) {
    char line[BUFFER_SIZE];
    char x_str[BUFFER_SIZE];
    char p_el_str[BUFFER_SIZE];

    // Read the key file line by line
    while (fgets(line, sizeof(line), keyFile)) {
        if (strncmp(line, "x=", 2) == 0) {
            sscanf(line, "x=%s\n", x_str);
        } else if (strncmp(line, "p=", 2) == 0) {
            sscanf(line, "p=%s\n", p_el_str);
        }
    }
    // Convert the strings back to mpz_t
    mpz_set_str(x, x_str, 62);
    mpz_set_str(p_el, p_el_str, 62);
}

void generateElGamalKeys() {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, rand());

    // Generate prime p
    mpz_urandomb(p_el, state, MIN_PRIME_BITS);
    mpz_nextprime(p_el, p_el);

    // Generate generator g
    mpz_set_ui(g, 2);

    // Generate private key x
    mpz_urandomm(x, state, p_el);

    // Compute public key y = g^x mod p
    mpz_powm(y, g, x, p_el);
    gmp_randclear(state);
}

void encryptElGamalFile(const char *filePath) {
    gmp_randstate_t state;
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_encrypted_file", "wb+");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }
    gmp_randinit_default(state);
    gmp_randseed_ui(state, rand());
    generateElGamalKeys();

    unsigned char buffer;
    while (fread(&buffer, sizeof(unsigned char), 1, in)) {
        mpz_set_ui(m, buffer);

        // Generate random k
        mpz_urandomm(k, state, p_el);

        // Compute a = g^k mod p
        mpz_powm(a, g, k, p_el);

        // Compute b = y^k * m mod p
        mpz_powm(b, y, k, p_el);
        mpz_mul(b, b, m);
        mpz_mod(b, b, p_el);
        char *a_base62 = mpz_get_str(NULL, 62, a);
        char *b_base62 = mpz_get_str(NULL, 62, b);
        fprintf(out, "%s %s\n", a_base62, b_base62);
        free(a_base62);
        free(b_base62);
    }
    storeKeysToFile(filePath, elGamalStore);
    clearElGamal();
    gmp_randclear(state);
    fclose(in);
    fclose(out);

    if (remove(filePath) != 0 || rename("temp_encrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

void decryptElGamalFile(const char *filePath) {
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_decrypted_file", "wb+");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }
    initializeElGamal();
    loadKeysFromFile(filePath, elGamalLoad);
    char a_str[BUFFER_SIZE], b_str[BUFFER_SIZE];
    while (fscanf(in, "%s %s", a_str, b_str) != EOF) {
        mpz_set_str(a, a_str, 62);
        mpz_set_str(b, b_str, 62);

        // Compute s = a^x mod p
        mpz_powm(s, a, x, p_el);

        // Compute m = b * s^(-1) mod p
        mpz_invert(s, s, p_el);
        mpz_mul(m, b, s);
        mpz_mod(m, m, p_el);

        unsigned char decryptedChar = (unsigned char)mpz_get_ui(m);
        fwrite(&decryptedChar, sizeof(unsigned char), 1, out);
    }
    fclose(in);
    fclose(out);
    clearElGamal();
    if (remove(filePath) != 0 || rename("temp_decrypted_file", filePath) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

EncryptionAlgorithm elgamal_algorithm = {
    .name = "ElGamal",
    .encrypt = encryptElGamalFile,
    .decrypt = decryptElGamalFile
};
