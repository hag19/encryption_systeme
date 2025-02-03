#include "plugin_manager.h"
#include <stdio.h>
#include <string.h>
#include "../types/constants.h"
#include "../algorithms/rsa.h"
#include "../algorithms/aes.h"
#include "../algorithms/elgamal.h"
#include "../algorithms/hill.h"
#include "../algorithms/diffie_hellman.h"
static EncryptionAlgorithm *algorithms[MAX_ALGORITHMS];
static int algorithm_count = 0;
static EncryptionAlgorithm *current_algorithm = NULL;

void register_algorithm(EncryptionAlgorithm *algorithm) {
    if (algorithm_count < MAX_ALGORITHMS) {
        algorithms[algorithm_count++] = algorithm;
    }
}
void register_existing_algorithms() {
    register_algorithm(&rsa_algorithm);
    register_algorithm(&aes_algorithm);
    register_algorithm(&elgamal_algorithm);
    register_algorithm(&hill_algorithm);
    register_algorithm(&diffie_hellman_algorithm);
}
void display_algorithms() {
    printf("Available algorithms:\n");
    for (int i = 0; i < algorithm_count; i++) {
        printf("%d. %s\n", i + 1, algorithms[i]->name);
    }
    printf("Choose your algorithm by id\n");
}

EncryptionAlgorithm* get_algorithm(const int choice) {
    if (choice > 0 && choice <= algorithm_count) {
        return algorithms[choice - 1];
    }
    return NULL;
}

int load_plugin(const char *plugin_path) {
#ifdef _WIN32
    HMODULE handle = LoadLibrary(plugin_path);
    if (!handle) {
        fprintf(stderr, "Error loading plugin: %lu\n", GetLastError());
        return -1;
    }
    EncryptionAlgorithm* (*get_algorithm)() = (EncryptionAlgorithm* (*)())GetProcAddress(handle, "get_algorithm");
    if (!get_algorithm) {
        fprintf(stderr, "Error finding symbol: %lu\n", GetLastError());
        FreeLibrary(handle);
        return -1;
    }
#else
    void *handle = dlopen(plugin_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading plugin: %s\n", dlerror());
        return -1;
    }
    EncryptionAlgorithm* (*get_algorithm)() = dlsym(handle, "get_algorithm");
    if (!get_algorithm) {
        fprintf(stderr, "Error finding symbol: %s\n", dlerror());
        dlclose(handle);
        return -1;
    }
#endif

    current_algorithm = get_algorithm();
    if (current_algorithm) {
        register_algorithm(current_algorithm);
        printf("Plugin loaded and algorithm registered: %s\n", current_algorithm->name);
        return algorithm_count - 1;
    } else {
        fprintf(stderr, "Error getting algorithm from plugin\n");
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        return -1;
    }
}
