# encryption_systeme

## Implemented Algorithms

The following encryption algorithms have been implemented in this project:

1. AES (Advanced Encryption Standard)
2. RSA (Rivest-Shamir-Adleman)
3. ElGamal
4. Hill Cipher
5. Diffie-Hellman

## Libraries Used

The following libraries have been used in this project:

1. GMP (GNU Multiple Precision Arithmetic Library) - Used for RSA, ElGamal, and Diffie-Hellman algorithms to handle big numbers.
2. Standard C Library - Used for file I/O, memory management, and other standard operations.

## Creating a Custom Encryption Algorithm

To create a custom encryption algorithm, you need to create a C file with the following structure:

```c
typedef struct {
    const char *name;
    void (*encrypt)(const char *filePath);
    void (*decrypt)(const char *filePath);
} EncryptionAlgorithm;

void your_encryption_func(const char *filePath) {
    printf("viva M.Trancho\n");
}

void your_decryption_func(const char *filePath) {
    printf("viva M.Trancho\n");
}

// Define your algorithm
EncryptionAlgorithm your_algorithm_name = {
    .name = "short_name_for_algorithm",
    .encrypt = your_encryption_func,
    .decrypt = your_decryption_func
};

// Implement the `get_algorithm` function
__attribute__((visibility("default"))) EncryptionAlgorithm* get_algorithm() {
    return &your_algorithm_name;
}
```

## Compiling the Custom Algorithm

Compile the custom algorithm into a shared object (.so) file:

```bash
gcc -fPIC -shared -o your_plugin.so your_plugin.c
```

## Registering the Custom Algorithm

You can register your custom algorithm via the plugin system. Run the main program and choose the option to register a custom algorithm. Provide the path to the compiled .so file when prompted.

## Running the Main Program

To compile and run the main program, use the following commands:

```bash
make
./bin/main
```
