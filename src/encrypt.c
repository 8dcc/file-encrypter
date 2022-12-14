/*
 * Functions for encrypting and decrypting text.
 *
 * https://github.com/r4v10l1/file-encrypter
 */

#include <stdio.h>
#include <string.h>    // For memcpy()

#include "lib/aes256.h"

#define BLOCK_SZ 16    // For readability
#define OUTPUT_FILE "output.txt"

void encrypt_file(char* filename) {
    // TODO: Parameter
    // 32 bytes (256 bits)
    const char key[] = "0123456789"
                       "0123456789"
                       "0123456789"
                       "01";

    printf("Using key: \"%s\"\n", key);
    printf("Encrypting text from file: \"%s\" to \"%s\"\n", filename, OUTPUT_FILE);

    /*----------------------------------------------------------*/

    aes256_context_t ctx;

    aes256_key_t aes_key;
    memcpy(&aes_key, key, sizeof(aes_key));

    aes256_init(&ctx, &aes_key);

    /*----------------------------------------------------------*/

    // TODO: Paddings to data and key, xor excess key with itself

    int c;
    FILE* fd = fopen(filename, "r");

    // Clear output file and open in append mode
    FILE* output = fopen(OUTPUT_FILE, "w");
    fclose(output);
    output = fopen(OUTPUT_FILE, "a");

    // Data block of 16 bytes (See lib/aes256.h)
    aes256_blk_t blk;

    // Will count the number of chars we wrote to the current block
    int cur_blk_sz = 0;

    while ((c = getc(fd)) != EOF) {
        // If the block is full, encrypt and reset blk pos
        if (cur_blk_sz >= BLOCK_SZ) {
            aes256_encrypt_ecb(&ctx, &blk);
            cur_blk_sz = 0;

            for (int i = 0; i < BLOCK_SZ; i++) {
                putc(blk.raw[i], output);
            }
        }

        // Write next char to block
        blk.raw[cur_blk_sz++] = c;
    }

    // If last block is incomplete, fill with zeros and encrypt one last time
    if (cur_blk_sz < BLOCK_SZ) {
        while (cur_blk_sz < BLOCK_SZ) {
            blk.raw[cur_blk_sz++] = '\0';
        }

        aes256_encrypt_ecb(&ctx, &blk);
        cur_blk_sz = 0;
        for (int i = 0; i < BLOCK_SZ; i++) {
            putc(blk.raw[i], output);
        }
    }

    fclose(fd);
    fclose(output);
}

void decrypt_file(char* filename) {}
