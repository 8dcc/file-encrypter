
#include <stdio.h>
#include <string.h>    // For strncpy()
#include <ctype.h>     // For tolower()

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
    char *in_filename, *out_filename;
    char password[255] = { 0 };

    // Read arguments
    int enc = 0, dec = 0, pass_prompt = 1, error = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;

        // We don't have to worry about "-" for stdin and stdout here because we know
        // what argv's are potential arguments or file names (after -e or -d)
        switch (argv[i][1]) {
            case 'e':
                if (!dec) {
                    enc = 1;

                    if (i + 2 >= argc) {
                        fprintf(stderr, "Not enough arguments for encrypting.\n");
                        error = 1;
                        break;
                    }

                    in_filename  = argv[++i];
                    out_filename = argv[++i];
                } else {
                    fprintf(stderr, "Can't encrypt and decrypt at the same time.\n");
                    error = 1;
                }
                break;
            case 'd':
                if (!enc) {
                    dec = 1;

                    if (i + 2 >= argc) {
                        fprintf(stderr, "Not enough arguments for decrypting.\n");
                        error = 1;
                        break;
                    }

                    in_filename  = argv[++i];
                    out_filename = argv[++i];
                } else {
                    fprintf(stderr, "Can't encrypt and decrypt at the same time.\n");
                    error = 1;
                }
                break;
            case 'p':
                // Don't ask for password
                pass_prompt = 0;

                if (i + 1 >= argc) {
                    fprintf(stderr, "Not enough arguments for password.\n");
                    error = 1;
                    break;
                }

                strncpy(password, argv[++i], sizeof(password));
                break;
            case 'h':
                error = 1;    // -h
                break;
            default:
                fprintf(stderr, "Unknown option: \'%c\'.\n", argv[i][1]);
                error = 1;
                break;
        }
    }

    // The program needs to do something
    if (!dec && !enc)
        error = 1;

    // Wrong args
    // TODO: -p, manpage
    if (error)
        die("Usage:\n"
            "    %s -h                   - Show this help\n"
            "    %s -e <input> <output>  - For encrypting the contents of input to "
            "output\n"
            "    %s -d <input> <output>  - For decrypting the contents of input to "
            "output\n\n"
            "Note: Using \"-\" as input or output will use stdin or stdout:\n"
            "    %s -e - -               - Read from stdin and write to stdout\n",
            argv[0], argv[0], argv[0], argv[0]);

    if (pass_prompt)
        password_prompt(password);

    if (enc)
        encrypt_file(in_filename, out_filename, password);
    else if (dec)
        decrypt_file(in_filename, out_filename, password);

    return 0;
}

