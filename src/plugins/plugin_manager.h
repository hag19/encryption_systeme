#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "../types/encryption_algorithm.h"

void register_algorithm(EncryptionAlgorithm *algorithm);
EncryptionAlgorithm* get_algorithm(const int choise);
int load_plugin(const char *plugin_path);
void display_algorithms();
#endif // PLUGIN_MANAGER_H
