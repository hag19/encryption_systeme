#ifndef KEY_HANDELING_H
#define KEY_HANDELING_H
void storeKeysToFile(const char *filepath,void (*storeKeysFormatFile)(FILE *keyFile));
void loadKeysFromFile(const char *filepath,void (*loadKeysFromFile)(FILE *keyFile));
#endif // KEY_HANDELING_H