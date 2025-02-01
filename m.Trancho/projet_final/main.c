#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/plugins/plugin_manager.h"
#include "src/algorithms/aes.h"
#include "src/algorithms/rsa.h"

void display_algorithms() {
    printf("Available algorithms:\n");
    printf("1. AES\n");
    printf("2. RSA\n");
    printf("3. Register custom algorithm\n");
}

void handle_aes() {
    char filePath[BUFFER_SIZE];
    char key[AES_KEY_SIZE];

    printf("Enter the file name: ");
    scanf("%s", filePath);

    aes_generate_key(key, AES_KEY_SIZE);
    printf("Generated AES key: %s\n", key);

    aes_initialize(key);
    aes_encrypt_file(filePath);

    printf("Encryption complete!\n");

    printf("Enter the AES key for decryption: ");
    scanf("%s", key);

    aes_decrypt_file(filePath, key);

    printf("Decryption complete!\n");
}

void handle_rsa() {
    char filePath[BUFFER_SIZE];
    mpz_t decryptionKey, modulus;

    mpz_inits(decryptionKey, modulus, NULL);

    printf("Enter the file name: ");
    scanf("%s", filePath);

    generateKeys(); // Generate p, q, n, e, and d for encryption

    encryptFile(filePath);

    gmp_printf("Encryption complete!\nPublic key (e, n): (%Zd, %Zd)\n", e, n);
    gmp_printf("Private key (d, n): (%Zd, %Zd)\n", d, n);

    printf("Enter the decryption key (d): ");
    gmp_scanf("%Zd", decryptionKey);
    printf("Enter the modulus (n): ");
    gmp_scanf("%Zd", modulus);

    decryptFile(filePath, decryptionKey, modulus);

    printf("Decryption complete!\n");

    mpz_clears(decryptionKey, modulus, NULL);
}

void handle_custom_algorithm() {
    char plugin_path[BUFFER_SIZE];

    printf("Enter the path to the custom algorithm plugin: ");
    scanf("%s", plugin_path);

    if (load_plugin(plugin_path) == 0) {
        printf("Custom algorithm loaded successfully.\n");
    } else {
        printf("Failed to load custom algorithm.\n");
    }
}

int main() {
    int choice;

    register_algorithm(&aes_algorithm);
    register_algorithm(&rsa_algorithm);

    while (1) {
        display_algorithms();
        printf("Choose an algorithm (or 0 to exit): ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                exit(0);
            case 1:
                handle_aes();
                break;
            case 2:
                handle_rsa();
                break;
            case 3:
                handle_custom_algorithm();
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}
