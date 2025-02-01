#include "rsa.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/constants.h"
mpz_t d, e, n, p, q, phi;

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
        mpz_urandomb(prime, state, 512); // Generate 512-bit prime
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
    initializeRSA();

    // Generate two 512-bit prime numbers p and q
    generatePrime(p);
    generatePrime(q);

    // Calculate n = p * q
    mpz_mul(n, p, q);

    // Calculate phi = (p-1) * (q-1)
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    mpz_set_ui(e, 65537); // Commonly used prime exponent

    // Calculate d such that e * d ≡ 1 (mod phi)
    modInverse(d, e, phi);

    // Print keys and modulus in base 10
    char publicKey[BUFFER_SIZE];
    char privateKey[BUFFER_SIZE];
    char modulus[BUFFER_SIZE];
    mpz_get_str(publicKey, 62, e); // Base 62 for numerical representation
    mpz_get_str(privateKey, 62, d);
    mpz_get_str(modulus, 62, n);

    printf("Generated public key: %s\n", publicKey);
    printf("Generated private key: %s\n", privateKey);
    printf("Modulus: %s\n", modulus);

}

void encryptFile(const char *filePath) {
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_encrypted_file", "wb");
    mpz_t plain, cipher;
    mpz_inits(plain, cipher, NULL);
    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }
    
    unsigned char buffer;
    while (fread(&buffer, sizeof(unsigned char), 1, in)) {
        mpz_set_ui(plain, buffer);
        mpz_powm(cipher, plain, e, n);
        size_t count;
        unsigned char *cipher_data = (unsigned char *)mpz_export(NULL, &count, 1, 1, 0, 0, cipher);
        fwrite(&count, sizeof(size_t), 1, out);
        fwrite(cipher_data, 1, count, out);
        free(cipher_data);
    }

    mpz_clears(plain, cipher, NULL);
    fclose(in);
    fclose(out);

    printf("Encryption complete!\n");
    clearRSA();
}
void decryptFile(const char *filePath) {
    mpz_t cipher, plain, key, modulus;
    mpz_inits(key, modulus, cipher, plain, NULL);
    FILE *in = fopen(filePath, "rb");
    FILE *out = fopen("temp_decrypted_file", "wb");

    if (!in || !out) {
        perror("Error opening file");
        if (in) fclose(in);
        if (out) fclose(out);
        exit(EXIT_FAILURE);
    }

    char keyStr[BUFFER_SIZE]; // Increased size for larger keys
    char modulusStr[BUFFER_SIZE]; // Increased size for larger modulus

    printf("Enter the decryption key (d): ");
    if (scanf("%1023s", keyStr) != 1) {
        fprintf(stderr, "Invalid decryption key input.\n");
        mpz_clears(key, modulus, NULL);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }
    if (mpz_set_str(key, keyStr, 62) != 0) {
        fprintf(stderr, "Invalid decryption key format.\n");
        mpz_clears(key, modulus, NULL);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }

    printf("Enter the modulus (n): ");
    if (scanf("%1023", modulusStr) != 1) {
        fprintf(stderr, "Invalid modulus input.\n");
        mpz_clears(key, modulus, NULL);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }
    if (mpz_set_str(modulus, modulusStr, 62) != 0) {
        fprintf(stderr, "Invalid modulus format.\n");
        mpz_clears(key, modulus, NULL);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }

    // Read the ciphertext from the file
    char buffer[BUFFER_SIZE];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), in);
    if (bytesRead == 0) {
        fprintf(stderr, "Error reading ciphertext from file.\n");
        mpz_clears(key, modulus, NULL);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0';

    if (mpz_set_str(cipher, buffer, 62) != 0) {
        fprintf(stderr, "Invalid ciphertext format.\n");
        mpz_clears(key, modulus, NULL);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }

    // Perform the decryption: plain = cipher^key mod modulus
    mpz_powm(plain, cipher, key, modulus);

    // Convert the plaintext to a string and write to the output file
    char *plainStr = mpz_get_str(NULL, 62, plain);
    fwrite(plainStr, 1, strlen(plainStr), out);
    free(plainStr);

    mpz_clears(key, modulus, cipher, plain, NULL);
    fclose(in);
    fclose(out);

    printf("Decryption complete!\n");
}
EncryptionAlgorithm rsa_algorithm = {
    .name = "RSA",
    .encrypt = encryptFile,
    .decrypt = decryptFile
};
