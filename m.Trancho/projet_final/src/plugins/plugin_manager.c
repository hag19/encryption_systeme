#include "plugin_manager.h"
#include "plugin_interface.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#define MAX_ALGORITHMS 10

static EncryptionAlgorithm *algorithms[MAX_ALGORITHMS];
static int algorithm_count = 0;

void register_algorithm(EncryptionAlgorithm *algorithm) {
    if (algorithm_count < MAX_ALGORITHMS) {
        algorithms[algorithm_count++] = algorithm;
    }
}

EncryptionAlgorithm* get_algorithm(const char *name) {
    for (int i = 0; i < algorithm_count; i++) {
        if (strcmp(algorithms[i]->name, name) == 0) {
            return algorithms[i];
        }
    }
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

    EncryptionAlgorithm *algorithm = get_algorithm();
    if (algorithm) {
        register_algorithm(algorithm);
        printf("Plugin loaded and algorithm registered: %s\n", algorithm->name);
        return 0;
    } else {
        fprintf(stderr, "Error getting algorithm from plugin\n");
        dlclose(handle);
        return -1;
    }
}