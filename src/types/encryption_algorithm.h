#ifndef ENCRYPTION_ALGORITHM_H
#define ENCRYPTION_ALGORITHM_H

typedef struct {
    const char *name;
    void (*encrypt)(const char *file);
    void (*decrypt)(const char *file);
} EncryptionAlgorithm;

#endif // ENCRYPTION_ALGORITHM_H

