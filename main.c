#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "src/plugins/plugin_manager.h"
#include "tests/benchmark.c"
#include "graphic.h"

void handle_existing_algorithm(int choice);
void load_custom_algorithm();
void display_message(const char *message);

void handle_existing_algorithm(int choice) {
    EncryptionAlgorithm* chosen_algorithm = get_algorithm(choice);
    if (chosen_algorithm) {
        char filePath[BUFFER_SIZE];
        display_message("Enter the file name: ");
        get_user_input(filePath, sizeof(filePath));

        display_message("1 for encryption\n2 for decryption\n3 benchmark the algorithm\n");
        char option_input[10];
        get_user_input(option_input, sizeof(option_input));
        int option = atoi(option_input);

        switch (option) {
            case 1:
                chosen_algorithm->encrypt(filePath);
                break;
            case 2:
                chosen_algorithm->decrypt(filePath);
                break;
            case 3:
                benchmark_algorithm(chosen_algorithm, filePath);
                break;
            default:
                display_message("Invalid choice.\n");
                break;
        }
    } else {
        display_message("Failed to retrieve algorithm.\n");
    }
}

void load_custom_algorithm() {
    char plugin_path[BUFFER_SIZE];
    display_message("Enter the path to the custom algorithm plugin: ");
    get_user_input(plugin_path, sizeof(plugin_path));

    int algorithm_index = load_plugin(plugin_path);
    if (algorithm_index != -1) {
        display_message("Custom algorithm loaded successfully.\n");
    } else {
        display_message("Failed to load custom algorithm.\n");
    }
}

void display_message(const char *message) {
    // Affiche le message sur la fenêtre SDL
    renderText(message, 220, 250); // Positionnez le texte comme vous le souhaitez
    SDL_Flip(screen); // Met à jour l'écran
}

int main() {
    int choice;
    register_existing_algorithms();

    initSDL(); // Initialisation de SDL
    drawFiles(); // Affiche les fichiers au démarrage

    while (1) {
        display_message("1 for existing algorithms 2 for custom (or 0 to exit): ");
        char choice_input[10];
        get_user_input(choice_input, sizeof(choice_input));
        choice = atoi(choice_input);

        switch (choice) {
            case 0:
                exit(0);
            case 1:
                display_algorithms();
                int algorithm_choice;
                char algorithm_choice_input[10];
                get_user_input(algorithm_choice_input, sizeof(algorithm_choice_input));
                algorithm_choice = atoi(algorithm_choice_input);
                handle_existing_algorithm(algorithm_choice);
                break;
            case 2:
                load_custom_algorithm();
                break;
            default:
                display_message("Invalid choice.\n");
                break;
        }

        // Lancer l'interface graphique
        drawFiles(); // Redessine les fichiers après chaque action
    }

    return 0;
}
