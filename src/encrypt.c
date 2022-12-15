/*
 * Functions for hashing, encrypting and decrypting text.
 *
 * https://github.com/r4v10l1/file-encrypter
 */

#include <stdio.h>
#include <string.h>    // For memcpy()

#include "lib/md5.h"    // Need to include md5 first because of uint8_t define in aes
#include "lib/aes256.h"

#include "misc.h"    // For die()

#define MD5_SZ   16    // For readability (16 bytes * 2 hex chars -> 32 bytes)
#define BLOCK_SZ 16    // For readability

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
 * encrypt_stream:
 *   Encrypts each 16 byte block that forms the contents of 'in' with the aes256
 *   algorithm, using the md5 hash of 'password' as key for aes256. Then appends each
 *   encrypted block into the 'out' file descriptor.
 */
void encrypt_stream(FILE* in, FILE* out, char* password) {
    // The 16 bytes of the hash * 2 chars for representing each byte in hex.
    // 16 bytes -> 32 chars -> 256 bits.
    hash_password(password);

    // Initialize aes256 context, copy password string into the aes256_key_t struct
    aes256_context_t ctx;

    aes256_key_t aes_key;
    memcpy(&aes_key, password, sizeof(aes_key));

    aes256_init(&ctx, &aes_key);

    /*------------------------------------------------------------------------*/

    int c;

    // Data block of 16 bytes (See lib/aes256.h)
    aes256_blk_t blk;

    // Will count the number of chars we wrote to the current block
    int cur_blk_sz = 0;

    while ((c = getc(in)) != EOF) {
        // If the block is full, encrypt and reset blk pos
        if (cur_blk_sz >= BLOCK_SZ) {
            aes256_encrypt_ecb(&ctx, &blk);
            cur_blk_sz = 0;

            for (int i = 0; i < BLOCK_SZ; i++) {
                putc(blk.raw[i], out);
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
            putc(blk.raw[i], out);
        }
    }

    aes256_done(&ctx);
    // We will close fd's in wrapper
}

/*
 * decrypt_stream:
 *   Decrypts each 16 byte block that forms the contents of 'in' with the aes256
 *   algorithm, using the md5 hash of 'password' as key for aes256. Then appends each
 *   decrypted block into the 'out' file descriptor.
 */
void decrypt_stream(FILE* in, FILE* out, char* password) {
    // The 16 bytes of the hash * 2 chars for representing each byte in hex.
    // 16 bytes -> 32 chars -> 256 bits.
    hash_password(password);

    // Initialize aes256 context, copy password string into the aes256_key_t struct
    aes256_context_t ctx;

    aes256_key_t aes_key;
    memcpy(&aes_key, password, sizeof(aes_key));

    aes256_init(&ctx, &aes_key);

    /*------------------------------------------------------------------------*/

    int c;

    // Data block of 16 bytes (See lib/aes256.h)
    aes256_blk_t blk;

    // Will count the number of chars we wrote to the current block
    int cur_blk_sz = 0;

    // Fill the block with encrypted bytes
    while ((c = getc(in)) != EOF) {
        // Write next char to block
        blk.raw[cur_blk_sz++] = c;

        // If the block is full, decrypt and reset blk pos
        if (cur_blk_sz >= BLOCK_SZ) {
            aes256_decrypt_ecb(&ctx, &blk);
            cur_blk_sz = 0;

            // Write the decrypted block to output but ignore null chars
            for (int i = 0; i < BLOCK_SZ && blk.raw[i] != '\0'; i++) {
                putc(blk.raw[i], out);
            }
        }
    }

    // The size of the input should be right (divisible by BLOCK_SZ), because is an
    // aes256 encrypted text.

    aes256_done(&ctx);
    // We will close fd's in wrapper
}

/* Wrappers for encrypt_stream and decrypt_stream */
void encrypt_file(char* in_filename, char* out_filename, char* password) {
    FILE* in = fopen(in_filename, "r");
    if (!in)
        die("Error. Can't open input file: \"%s\"\n", in_filename);

    // Clear output file
    FILE* out = fopen(out_filename, "w");
    if (!out)
        die("Error. Can't open output file: \"%s\"\n", out_filename);
    fclose(out);

    out = fopen(out_filename, "a");
    if (!out)
        die("Error. Can't open output file: \"%s\"\n", out_filename);

    encrypt_stream(in, out, password);

    fclose(in);
    fclose(out);
}

void decrypt_file(char* in_filename, char* out_filename, char* password) {
    FILE* in = fopen(in_filename, "r");
    if (!in)
        die("Error. Can't open input file: \"%s\"\n", in_filename);

    // Clear output file
    FILE* out = fopen(out_filename, "w");
    if (!out)
        die("Error. Can't open output file: \"%s\"\n", out_filename);
    fclose(out);

    out = fopen(out_filename, "a");
    if (!out)
        die("Error. Can't open output file: \"%s\"\n", out_filename);

    decrypt_stream(in, out, password);

    fclose(in);
    fclose(out);
}

