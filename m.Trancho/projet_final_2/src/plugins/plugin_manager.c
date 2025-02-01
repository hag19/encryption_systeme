#include "plugin_manager.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include "../types/constants.h"
static EncryptionAlgorithm *algorithms[MAX_ALGORITHMS];
static int algorithm_count = 0;
static EncryptionAlgorithm *current_algorithm = NULL;
void register_algorithm(EncryptionAlgorithm *algorithm) {
    if (algorithm_count < MAX_ALGORITHMS) {
        algorithms[algorithm_count++] = algorithm;
    }
}
void display_algorithms() {
    printf("Available algorithms:\n");
    for (int i = 0; i < algorithm_count; i++) {
        printf("%d. %s\n", i + 1, algorithms[i]->name);
    }
    printf("chose your algorithm by id\n");
}
EncryptionAlgorithm* get_algorithm(const int choise) {
            return algorithms[choise - 1];
    return NULL;
}

int load_plugin(const char *plugin_path) {
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
    current_algorithm = get_algorithm();
    if (current_algorithm) {
        register_algorithm(current_algorithm);
        printf("Plugin loaded and algorithm registered: %s\n", current_algorithm->name);
        return algorithm_count - 1;
    } else {
        fprintf(stderr, "Error getting algorithm from plugin\n");
        dlclose(handle);
        return -1;
    }
}