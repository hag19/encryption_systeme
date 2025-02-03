#include "../types/constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
void storeKeysToFile(const char *filepath,void (*storeKeysFormatFile)(FILE *keyFile)) {
    // Create the .key file
    char keyFilePath[BUFFER_SIZE];
    snprintf(keyFilePath, sizeof(keyFilePath), "%s.key", filepath);

    FILE *keyFile = fopen(keyFilePath, "wb+");
    if (!keyFile) {
        perror("Error creating key file");
        exit(EXIT_FAILURE);
    }
    if(storeKeysFormatFile){
        storeKeysFormatFile(keyFile);
    }else{
        printf("storeKeysFormatFile is not implemented or not providede correctly\n"); 
    }
    // Set file permissions: readable only by the owner (rw-------)
    chmod(keyFilePath, S_IRUSR | S_IWUSR);

    printf("Keys have been stored in %s with appropriate permissions.\n", keyFile);
}

void loadKeysFromFile(const char *filepath,void (*loadKeysFromFile)(FILE *keyFile)) {
    // Construct the .key file path
    char keyFilePath[BUFFER_SIZE];
    snprintf(keyFilePath, sizeof(keyFilePath), "%s.key", filepath);

    FILE *keyFile = fopen(keyFilePath, "rb");
    if (!keyFile) {
        perror("Error opening key file");
        exit(EXIT_FAILURE);
    }
 if(loadKeysFromFile){
        loadKeysFromFile(keyFile);
    }else{
        printf("loadKeysFormatFile is not implemented or not providede correctly\n"); 
    }
    printf("Keys have been loaded from %s.\n", keyFile);
}