/*
 * Functions for encrypting and decrypting text.
 *
 * https://github.com/r4v10l1/file-encrypter
 */

#include <stdio.h>

#include "lib/aes256.h"

void encrypt_file(char* filename) {
    // 32 bytes (256 bits)
    const char key[] = "0123456789"
                       "0123456789"
                       "0123456789"
                       "01";

    printf("Using key: \"%s\"\n", key);
    printf("Encrypting text: \"%s\"\n", filename);

    // TODO: Paddings to data and key, xor excess key with itself
}

void decrypt_file(char* filename) {}
