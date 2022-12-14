
#include <stdio.h>
#include <ctype.h>    // For tolower()

#include "misc.h"
#include "encrypt.h"

static inline void password_prompt(char* dst) {
    printf("Password: ");
    fgets(dst, 255, stdin);

    // Replace the first '\n' with '\0' (Remove newline)
    while (*dst++ != '\0') {
        if (*dst == '\n') {
            *dst = '\0';
            break;
        }
    }
}

int main(int argc, char** argv) {
    // Not enough args
    if (argc < 3)
        die("Usage:\n"
            "    %s -e <filename>   - For encrypting a file\n"
            "    %s -d <filename>   - For decrypting a file\n",
            argv[0], argv[0]);

    // Not -e or -d
    if (argv[1][0] != '-')
        die("Error. Unknown parameter: \"%s\"\n", argv[1]);

    char password[255] = { 0 };

    // Check first param
    switch (tolower(argv[1][1])) {
        case 'e':
            password_prompt(password);
            encrypt_file(argv[2], password);
            break;
        case 'd':
            password_prompt(password);
            decrypt_file(argv[2], password);
            break;
        default:
            die("Error. Unknown parameter: \"%s\"\n", argv[1]);
    }

    return 0;
}

