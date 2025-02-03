#ifndef HILL_H
#define HILL_H

#include "../types/encryption_algorithm.h"
#include "../types/constants.h"

int calculateDeterminant(int keyMatrix[3][3]);
int gcd_hill(int a, int b);
int isKeyValid(int keyMatrix[3][3]);
void generateValidKey(char key[10]);
void getKeyMatrix(const char *key, int keyMatrix[3][3]);
int modInverseHill(int a, int m);
int getInverseKeyMatrix(int keyMatrix[3][3], int inverseKeyMatrix[3][3]);
void encrypt(int cipherMatrix[3][1], int keyMatrix[3][3], int messageVector[3][1]);
void decrypt(int messageVector[3][1], int inverseKeyMatrix[3][3], int cipherMatrix[3][1]);
void encryptHillFile(const char *filePath);
void decryptHillFile(const char *filePath);

extern EncryptionAlgorithm hill_algorithm;

#endif // HILL_H
