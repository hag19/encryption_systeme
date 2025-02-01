#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XOR_KEY_SIZE 16
typedef struct {
    const char *name;
    void (*encrypt)(const char *filePath);
    void (*decrypt)(const char *filePath);
} EncryptionAlgorithm;

void xor_encrypt_file(const char *filePath) {
 printf("encrypt");
}

void xor_decrypt_file(const char *filePath) {
 printf("decrypt");
}

EncryptionAlgorithm xor_algorithm = {
    .name = "XOR",
    .encrypt = xor_encrypt_file,
    .decrypt = xor_decrypt_file
};