#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "../types/encryption_algorithm.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

void register_algorithm(EncryptionAlgorithm *algorithm);
EncryptionAlgorithm* get_algorithm(const int choice);
int load_plugin(const char *plugin_path);
void display_algorithms();

#endif // PLUGIN_MANAGER_H
