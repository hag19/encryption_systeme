#include <stdio.h>
#include "plugins/plugin_manager.h"
#include "algorithms/aes.h"
#include "algorithms/rsa.h"


int main() {
    register_algorithm(&aes_algorithm);
    register_algorithm(&rsa_algorithm);

    char command[256];
    while (1) {
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character
        if (strcmp(command, "exit") == 0) {
            break;
        }
        execute_command(command);
    }

    return 0;
}