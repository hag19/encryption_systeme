#include "hill.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h> // For toupper()
#include "../types/constants.h"
#include "key_handeling.h"

char keyHill[10];

// Function to calculate the determinant of a 3x3 matrix
int calculateDeterminant(int keyMatrix[3][3]) {
    return keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1])
         - keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0])
         + keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
}

// Function to compute the greatest common divisor (gcd_hill) of two numbers
int gcd_hill(int a, int b) {
    if (b == 0)
        return a;
    return gcd_hill(b, a % b);
}

// Function to check if the determinant is valid (non-zero and coprime with 26)
int isKeyValid(int keyMatrix[3][3]) {
    int det = calculateDeterminant(keyMatrix);
    det = (det % 26 + 26) % 26; // Ensure determinant is positive
    return (det != 0 && gcd_hill(det, 26) == 1);
}

// Function to generate a valid Hill cipher key
void generateValidKey(char key[10]) {
    int keyMatrix[3][3];
    srand(time(NULL)); // Seed the random number generator

    do {
        // Generate a random 3x3 matrix
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                keyMatrix[i][j] = rand() % 26; // Random number between 0 and 25
            }
        }
    } while (!isKeyValid(keyMatrix)); // Repeat until a valid key is found

    // Convert the matrix to a 9-letter key
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            key[k++] = keyMatrix[i][j] + 'A'; // Convert numbers to letters (A-Z)
        }
    }
    key[9] = '\0'; // Null-terminate the key string
}

void getKeyMatrix(const char *key, int keyMatrix[3][3]) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            keyMatrix[i][j] = (toupper(key[k]) - 'A') % 26; // Ensure uppercase
            k++;
        }
    }
}

int modInverseHill(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int getInverseKeyMatrix(int keyMatrix[3][3], int inverseKeyMatrix[3][3]) {
    int det = keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1])
            - keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0])
            + keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    
    det = (det % 26 + 26) % 26;
    printf("Determinant: %d\n", det);
    
    int detInv = modInverseHill(det, 26);
    printf("Determinant Inverse: %d\n", detInv);
    
    if (detInv == -1) return 0;
    
    int adj[3][3] = {
        { (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]), -(keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1]), (keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1]) },
        { -(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]), (keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]), -(keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0]) },
        { (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]), -(keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0]), (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) }
    };
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverseKeyMatrix[i][j] = (detInv * adj[i][j]) % 26;
            if (inverseKeyMatrix[i][j] < 0)
                inverseKeyMatrix[i][j] += 26;
        }
    }
    return 1;
}

void encrypt(int cipherMatrix[3][1], int keyMatrix[3][3], int messageVector[3][1]) {
    for (int i = 0; i < 3; i++) {
        cipherMatrix[i][0] = 0;
        for (int j = 0; j < 3; j++) {
            cipherMatrix[i][0] += keyMatrix[i][j] * messageVector[j][0];
        }
        cipherMatrix[i][0] %= 26;
    }
}

void decrypt(int messageVector[3][1], int inverseKeyMatrix[3][3], int cipherMatrix[3][1]) {
    for (int i = 0; i < 3; i++) {
        messageVector[i][0] = 0;
        for (int j = 0; j < 3; j++) {
            messageVector[i][0] += inverseKeyMatrix[i][j] * cipherMatrix[j][0];
        }
        messageVector[i][0] %= 26;
    }
}

void Hillstore(FILE *keyFile) {
    fprintf(keyFile, "%s\n", keyHill);
    fprintf(keyFile,"key=%s\n", keyHill);
}

void Hillload(FILE *keyFile) {
    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), keyFile)) {
        if (strncmp(line, "key=", 4) == 0) {
            sscanf(line, "key=%s\n", keyHill);
        }
    }
    printf("Loaded key: %s\n", keyHill);
}

void encryptHillFile(const char *filepath) {
    FILE *in = fopen(filepath, "rb");
    FILE *out = fopen("tmp_encrypted_file", "wb+");
    if (!in || !out) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    generateValidKey(keyHill); // Generate a valid key
    storeKeysToFile(filepath, Hillstore);
    int keyMatrix[3][3];
    getKeyMatrix(keyHill, keyMatrix);

    char message[3];
    while (fread(message, 1, 3, in) == 3) {
        int messageVector[3][1];
        for (int i = 0; i < 3; i++) {
            messageVector[i][0] = (toupper(message[i]) - 'A') % 26; // Ensure uppercase
        }

        int cipherMatrix[3][1];
        encrypt(cipherMatrix, keyMatrix, messageVector);

        for (int i = 0; i < 3; i++) {
            message[i] = cipherMatrix[i][0] + 'A'; // Convert back to uppercase letter
        }
        fwrite(message, 1, 3, out);
    }

    fclose(in);
    fclose(out);
    if (rename("tmp_encrypted_file", filepath) != 0) {
        perror("Error replacing original file with encrypted file");
        exit(EXIT_FAILURE);
    }
    printf("Encryption complete! File updated with encrypted data.\n");
}

void decryptHillFile(const char *filepath) {
    FILE *in = fopen(filepath, "rb");
    FILE *out = fopen("tmp_decrypted_file", "wb+");
    if (!in || !out) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Load the key from the file
    loadKeysFromFile(filepath, Hillload);
    int keyMatrix[3][3], inverseKeyMatrix[3][3];
    getKeyMatrix(keyHill, keyMatrix);
    if (!getInverseKeyMatrix(keyMatrix, inverseKeyMatrix)) {
        printf("Invalid key. Decryption not possible.\n");
        fclose(in);
        fclose(out);
        return;
    }

    char cipherText[3];
    while (fread(cipherText, 1, 3, in) == 3) {
        int cipherMatrix[3][1];
        for (int i = 0; i < 3; i++) {
            cipherMatrix[i][0] = (toupper(cipherText[i]) - 'A') % 26; // Ensure uppercase
        }

        int messageVector[3][1];
        decrypt(messageVector, inverseKeyMatrix, cipherMatrix);

        for (int i = 0; i < 3; i++) {
            cipherText[i] = messageVector[i][0] + 'A'; // Convert back to uppercase letter
        }
        fwrite(cipherText, 1, 3, out);
    }

    fclose(in);
    fclose(out);
    if (rename("tmp_decrypted_file", filepath) != 0) {
        perror("Error replacing original file with decrypted file");
        exit(EXIT_FAILURE);
    }
    printf("Decryption complete! File updated with decrypted data.\n");
}

EncryptionAlgorithm hill_algorithm = {
    .name = "Hill",
    .encrypt = encryptHillFile,
    .decrypt = decryptHillFile
};