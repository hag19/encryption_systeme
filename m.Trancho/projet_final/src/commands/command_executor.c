#include "command_executor.h"
#include <stdio.h>
#include <string.h>
#include "../plugins/plugin_manager.h"

void execute_command(const char *command) {
    char cmd[256];
    char arg1[256];
    char arg2[256];
    sscanf(command, "%s %s %s", cmd, arg1, arg2);

    if (strcmp(cmd, "encrypt") == 0) {
        EncryptionAlgorithm *algorithm = get_algorithm(arg1);
        if (algorithm) {
            char output[256];
            algorithm->encrypt(arg2, output);
            printf("Encrypted: %s\n", output);
        } else {
            printf("Algorithm not found\n");
        }
    } else if (strcmp(cmd, "decrypt") == 0) {
        EncryptionAlgorithm *algorithm = get_algorithm(arg1);
        if (algorithm) {
            char output[256];
            algorithm->decrypt(arg2, output);
            printf("Decrypted: %s\n", output);
        } else {
            printf("Algorithm not found\n");
        }
    } else {
        printf("Unknown command\n");
    }
}