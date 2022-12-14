
#include <stdio.h>
#include <ctype.h>    // For tolower()

#include "misc.h"
#include "encrypt.h"

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

    // Check first param
    switch (tolower(argv[1][1])) {
        case 'e':
            encrypt_file(argv[2]);
            break;
        case 'd':
            decrypt_file(argv[2]);
            break;
        default:
            die("Error. Unknown parameter: \"%s\"\n", argv[1]);
    }

    return 0;
}

