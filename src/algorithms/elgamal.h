#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <gmp.h>
#include "../types/encryption_algorithm.h"

// Function declarations
void initializeElGamal();
void clearElGamal();
void generateElGamalKeys();
void encryptElGamalFile(const char *filePath);
void decryptElGamalFile(const char *filePath);

extern EncryptionAlgorithm elgamal_algorithm;

#endif // ELGAMAL_H
