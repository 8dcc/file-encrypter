/*
 * Functions for hashing, encrypting and decrypting text.
 *
 * https://github.com/r4v10l1/file-encrypter
 */

void hash_password(char* password);

// Wrappers for encrypt_stream
void encrypt_file(char* in_filename, char* out_filename, char* password);
void decrypt_file(char* in_filename, char* out_filename, char* password);

void encrypt_stream(FILE* in, FILE* out, char* password);
void decrypt_stream(FILE* in, FILE* out, char* password);

