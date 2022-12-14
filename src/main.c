
#include <stdio.h>
#include "decrypt.h"
#include "encrypt.h"
#include "misc.h"
#include "settings.h"

int main() {
    printf("[E/D] Select mode: ");

    switch (getchar()) {
        case 'e':
        case 'E':
            encrypt();
            break;
        case 'd':
        case 'D':
            decrypt();
            break;
        default:
            fprintf(stderr, "Wrong option...\n");
            return 1;
    }

    return 0;
}

