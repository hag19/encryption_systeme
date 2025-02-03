#ifndef DIFFIE_HELLMAN_H
#define DIFFIE_HELLMAN_H
#include <stdio.h>
#include "../types/encryption_algorithm.h"

// Function declarations
void initializeDiffieHellman();
void clearDiffieHellman();
void generateDiffieHellmanKeys();
void computeSharedSecret();
void encryptDiffieHellmanFile(const char *filePath);
void decryptDiffieHellmanFile(const char *filePath);
void dhStore(FILE *keyFile);
void dhLoad(FILE *keyFile);
extern EncryptionAlgorithm diffie_hellman_algorithm;

#endif // DIFFIE_HELLMAN_H
