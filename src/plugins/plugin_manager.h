#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "encryption_algorithm.h"

void register_algorithm(EncryptionAlgorithm *algorithm);
EncryptionAlgorithm* get_algorithm(const char *name);
int load_plugin(const char *plugin_path);

#endif // PLUGIN_MANAGER_H