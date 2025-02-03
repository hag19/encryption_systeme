#include "src/plugins/plugin_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/types/constants.h"
#include "tests/benchmark.h"  // Include benchmark header file

void handle_existing_algorithm(int choice) {
    EncryptionAlgorithm* chosen_algorithm = get_algorithm(choice);
    if (chosen_algorithm) {
        char filePath[BUFFER_SIZE];
        printf("Enter the file name: ");
        scanf("%s", filePath);
        printf("1 for encryption\n2 for decryption\n3 benchmark the algorithm\n");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 1:
                chosen_algorithm->encrypt(filePath);
                break;
            case 2:
                chosen_algorithm->decrypt(filePath);
                break;
            case 3:
                benchmark_algorithm(chosen_algorithm, filePath);  // Ensure this matches your declaration
                break;    
            default:
                printf("Invalid choice.\n");
                break;
        }
    } else {
        printf("Failed to retrieve algorithm.\n");
    }
}

void load_custom_algorithm() {
    char plugin_path[BUFFER_SIZE];
    printf("Enter the path to the custom algorithm plugin: ");
    scanf("%s", plugin_path);

    int algorithm_index = load_plugin(plugin_path);
    if (algorithm_index != -1) {
        printf("Custom algorithm loaded successfully.\n");
    } else {
        printf("Failed to load custom algorithm.\n");
    }
}

int main() {
    int choice;
    register_existing_algorithms();
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
                load_custom_algorithm();
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;  // Ensure proper closing of main
}
