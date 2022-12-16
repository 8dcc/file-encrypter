
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
    if (error)
        die("SYNOPSIS\n"
            "       %s [-h] [-p password] -e|-d input output\n"
            "\n"
            "OPTIONS\n"
            "       -h     Show this help.\n"
            "\n"
            "       -p password\n"
            "              Use  password when encrypting or decrypting the file, "
            "instead of\n"
            "              asking for one\n"
            "\n"
            "       -e input output\n"
            "              Encrypts data from input and writes to output.  They can "
            "be file\n"
            "              names  or  in  the case of '-' it will read/write from "
            "stdin and\n"
            "              stdout.  Keep in mind that if you don't use -p, it will  "
            "try  to\n"
            "              read the password from stdin as well.\n"
            "\n"
            "       -d input output\n"
            "              Decrypts  data  from input and writes to output.  Just "
            "like with\n"
            "              -e, they can be file names  or  in  the  case  of  '-'  "
            "it  will\n"
            "              read/write from stdin and stdout.\n"

            "\n"
            "EXAMPLES\n"
            "       file-encrypter -e input.txt output.txt\n"
            "              Will  encrypt  the  contents of input.txt and write them "
            "to out-\n"
            "              put.txt.\n"
            "\n"
            "       file-encrypter -p \"t3st!\" -d input.txt output.txt\n"
            "              Will decrypt the contents of input.txt using \"t3st!\" "
            "as password\n"
            "              and write them to output.txt.\n"
            "\n"
            "       cat some-stuff.txt | file-encrypter -p \"my-p4ss\" -e - "
            "output.txt\n"
            "              Will  encrypt  the  contents  of stdin (in this case "
            "what he got\n"
            "              from the cat(1) pipe) using \"my-p4ss\" as password and "
            "write them\n"
            "              to output.txt.\n",
            argv[0]);

    if (pass_prompt)
        password_prompt(password);

    if (enc)
        encrypt_file(in_filename, out_filename, password);
    else if (dec)
        decrypt_file(in_filename, out_filename, password);

    return 0;
}

