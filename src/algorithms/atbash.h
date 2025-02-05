#ifndef ATBASH_H
#define ATBASH_H

#include "../types/encryption_algorithm.h"

void atbash_cipher(char *input, char *output);
void atbash_encrypt(const char *filepath);
void atbash_decrypt(const char *filepath);

extern EncryptionAlgorithm atbash_algorithm;

#endif // ATBASH_H