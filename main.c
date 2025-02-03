#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/plugins/plugin_manager.h"
#include "src/algorithms/aes.h"
#include "src/algorithms/rsa.h"
#include "src/algorithms/elgamal.h"
#include "src/types/constants.h"
#include "src/algorithms/hill.h"
#include "src/algorithms/diffie_hellman.h"
void handle_existing_algorithm(int choice) {
    EncryptionAlgorithm* chosen_algorithm = get_algorithm(choice);
    if (chosen_algorithm) {
        char filePath[BUFFER_SIZE];
        printf("Enter the file name: ");
        scanf("%s", filePath);
        printf("1 for encryption\n2 for decryption\n");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 1:
                chosen_algorithm->encrypt(filePath);
                break;
            case 2:
                chosen_algorithm->decrypt(filePath);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } else {
        printf("Failed to retrieve algorithm.\n");
    }
}

void handle_custom_algorithm() {
    char plugin_path[BUFFER_SIZE];
    printf("Enter the path to the custom algorithm plugin: ");
    scanf("%s", plugin_path);

    int algorithm_index = load_plugin(plugin_path);
    if (algorithm_index != -1) {
        printf("Custom algorithm loaded successfully.\n");

        EncryptionAlgorithm *custom_algorithm = get_algorithm(algorithm_index);
        if (custom_algorithm) {
            char filePath[BUFFER_SIZE];
            int choice;
            printf("Enter the file name: ");
            scanf("%s", filePath);
            printf("1 for encryption\n2 for decryption\n");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    custom_algorithm->encrypt(filePath); 
                    break;
                case 2:
                    custom_algorithm->decrypt(filePath); 
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        } else {
            printf("Failed to retrieve custom algorithm.\n");
        }
    } else {
        printf("Failed to load custom algorithm.\n");
    }
}

int main() {
    int choice;
    register_algorithm(&rsa_algorithm);
    register_algorithm(&aes_algorithm);  
    register_algorithm(&elgamal_algorithm);
    register_algorithm(&hill_algorithm);
    register_algorithm(&diffie_hellman_algorithm);
    while (1) {
        printf("1 for existing algorithms 2 for custom (or 0 to exit): ");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                exit(0);
            case 1:
                display_algorithms();
                int algorithm_choice;
                scanf("%d", &algorithm_choice);
                handle_existing_algorithm(algorithm_choice);
                break;
            case 2:
                handle_custom_algorithm();
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}
