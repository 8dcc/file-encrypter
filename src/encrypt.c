/*
 * Functions for encrypting and decrypting text.
 *
 * https://github.com/r4v10l1/file-encrypter
 */

#include <stdio.h>
#include <string.h>    // For memcpy()

#include "lib/md5.h"    // Need to include md5 first because of uint8_t define in aes
#include "lib/aes256.h"

#define MD5_SZ      16    // For readability (16 bytes * 2 hex chars -> 32 bytes)
#define BLOCK_SZ    16    // For readability
#define OUTPUT_FILE "output.txt"

/* hash_password: Writes the md5 hash of the original string as hex into the same
 * string. String needs to be at least 33 bytes long (32 + null terminator) */
void hash_password(char* password) {
    const uint8_t* hash = md5String(password);

    int i;
    for (i = 0; i < MD5_SZ; i++)
        sprintf(&password[i * 2], "%02x", hash[i]);

    password[i * 2] = '\0';
}

/*
 * encrypt_file:
 *   Encrypts each 16 byte block that forms the contents of 'filename' with the
 *   aes256 algorithm, using the md5 hash of 'password' as key for aes256. Then
 *   appends each encrypted block into OUTPUT_FILE.
 */
void encrypt_file(char* filename, char* password) {
    printf("Using md5 hash of password as key: \"%s\" -> ", password);

    // The 16 bytes of the hash * 2 chars for representing each byte in hex.
    // 16 bytes -> 32 chars -> 256 bits.
    hash_password(password);

    printf("\"%s\"\n", password);
    printf("Encrypting text from file: \"%s\" to \"%s\"\n", filename, OUTPUT_FILE);

    /*------------------------------------------------------------------------*/

    // Initialize aes256 context, copy password string into the aes256_key_t struct
    aes256_context_t ctx;

    aes256_key_t aes_key;
    memcpy(&aes_key, password, sizeof(aes_key));

    aes256_init(&ctx, &aes_key);

    /*------------------------------------------------------------------------*/

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

    aes256_done(&ctx);
    fclose(fd);
    fclose(output);
}

void decrypt_file(char* filename, char* password) {}
