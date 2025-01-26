#ifndef ENCRYPTION_ALGORITHM_H
#define ENCRYPTION_ALGORITHM_H

typedef struct {
    const char *name;
    void (*encrypt)(const char *input, char *output);
    void (*decrypt)(const char *input, char *output);
} EncryptionAlgorithm;

#endif // ENCRYPTION_ALGORITHM_H

