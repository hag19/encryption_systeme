#include "diffie_hellman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gmp.h>
#include "../types/constants.h"
#include "key_handeling.h"
#include "aes.h"
mpz_t dh_p, dh_g, dh_a, dh_A, dh_B, shared_secret;

void initializeDiffieHellman() {
    mpz_inits(dh_p, dh_g, dh_a, dh_A, dh_B, shared_secret, NULL);
    srand(time(NULL)); // Seed the random number generator
}

void clearDiffieHellman() {
    mpz_clears(dh_p, dh_g, dh_a, dh_A, dh_B, shared_secret, NULL);
}

void generateDiffieHellmanKeys() {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, rand());
    int choice;
    printf("you have p and g? 1 for yes 2 for no\n");
    scanf("%d",&choice);
    if(choice==1){
        char p_str[BUFFER_SIZE];
        char g_str[BUFFER_SIZE];
        printf("Enter the prime (p) and generator (g): \n");
        scanf("%s %s", p_str, g_str);
        mpz_set_str(dh_p, p_str, 62);
        mpz_set_str(dh_g, g_str, 62);
    }else{
    // Generate prime dh_p
    mpz_urandomb(dh_p, state, MIN_PRIME_BITS);
    mpz_nextprime(dh_p, dh_p);

    // Generate generator dh_g
    mpz_set_ui(dh_g, 2);
    }

    // Generate private key dh_a
    mpz_urandomm(dh_a, state, dh_p);

    // Compute public key dh_A = dh_g^dh_a mod dh_p
    mpz_powm(dh_A, dh_g, dh_a, dh_p);


    char *dh_A_base62 = mpz_get_str(NULL, 62, dh_A);
    char *dh_a_base62 = mpz_get_str(NULL, 62, dh_a);
    free(dh_A_base62);
    free(dh_a_base62);

    gmp_randclear(state);
}

void computeSharedSecret() {
    // Compute shared secret s = dh_B^dh_a mod dh_p
    printf("Enter the public key of the other party (B): \n");
    char dh_B_base62[BUFFER_SIZE];
    scanf("%s", dh_B_base62);
    mpz_set_str(dh_B, dh_B_base62, 62);
    mpz_powm(shared_secret, dh_B, dh_a, dh_p);
    char *shared_secret_base62 = mpz_get_str(NULL, 62, shared_secret);
    printf("Computed shared secret: %s\n", shared_secret_base62);
    free(shared_secret_base62);
}

void dhStore(FILE *keyFile) {
    // Write public key (e), private key (d), and modulus (n) to the file
    char *dh_A_base62 = mpz_get_str(NULL, 62, dh_A);
    char *dh_a_base62 = mpz_get_str(NULL, 62, dh_a);
    char *dh_p_base62 = mpz_get_str(NULL, 62, dh_p);
    char *dh_g_base62 = mpz_get_str(NULL, 62, dh_g);
    char *shared_key_base62 = mpz_get_str(NULL, 62, shared_secret);
    fprintf(keyFile, "A=%s\n", dh_A_base62);
    fprintf(keyFile, "a=%s\n", dh_a_base62);
    fprintf(keyFile, "p=%s\n", dh_p_base62);
    fprintf(keyFile, "g=%s\n", dh_g_base62);
    fprintf(keyFile, "shared_key=%s\n", shared_key_base62);
    printf("Generated public key (p, g, A): (%s, %s, %s)\nGenerated private key (a): (%s)\n", dh_p_base62, dh_g_base62,dh_A_base62,dh_a_base62);
    free(dh_A_base62);
    free(dh_a_base62);
    free(dh_p_base62);
    free(dh_g_base62);
    free(shared_key_base62);
}

// Function to load keys from a .key file
void dhLoad(FILE *keyFile) {
    char shared_key_base62[BUFFER_SIZE];
    char line[BUFFER_SIZE];
    // Read the key file line by line
    while (fgets(line, sizeof(line), keyFile)) {
        if(strncmp(line,"shared_key=",2)==0){
            sscanf(line,"shared_key=%s\n",shared_key_base62);
        }
    }
    // Convert the strings back to mpz_t
    mpz_set_str(shared_secret,shared_key_base62,62);
}
void encryptDiffieHellmanFile(const char *filePath) {
    initializeDiffieHellman();
    generateDiffieHellmanKeys();
    computeSharedSecret();
    storeKeysToFile(filePath, dhStore);
    aes_encrypt_file(filePath);
    clearDiffieHellman();
}

void decryptDiffieHellmanFile(const char *filePath) {
    initializeDiffieHellman();
    loadKeysFromFile(filePath, dhLoad);
    char *shared_key_base62=mpz_get_str(NULL,62,shared_secret);
    save_key(shared_key_base62);
    aes_decrypt_file(filePath);
    clearDiffieHellman();
}

EncryptionAlgorithm diffie_hellman_algorithm = {
    .name = "Diffie-Hellman",
    .encrypt = encryptDiffieHellmanFile,
    .decrypt = decryptDiffieHellmanFile
};
