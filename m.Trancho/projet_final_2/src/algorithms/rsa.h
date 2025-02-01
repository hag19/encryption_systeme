#ifndef RSA_H
#define RSA_H

#include "gmp.h"
#include "../types/encryption_algorithm.h"

// Function declarations
void initializeRSA();
void clearRSA();
int isPrime(mpz_t num);
void generatePrime(mpz_t prime);
void gcd(mpz_t result, mpz_t a, mpz_t b);
void modInverse(mpz_t result, mpz_t e, mpz_t phi);
void generateKeys();
void encryptFile(const char *filePath);
void decryptFile(const char *filePath);

extern EncryptionAlgorithm rsa_algorithm;

// Global variables for RSA
extern mpz_t p, q, n, phi, e, d;

#endif // RSA_H
