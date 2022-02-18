/*
 * https://github.com/r4v10l1/file-encrypter
 */

#include <stdio.h>
#include "settings.h"
#include "misc.h"
#include "encrypt.h"
#include "decrypt.h"

int main() {
	char mode;

	printf("[E/D] Select mode: ");
	mode = getchar();
	
	switch (mode) {
		case 'E':
			encrypt();
			break;
		case 'e':
			encrypt();
			break;
		case 'D':
			decrypt();
			break;
		case 'd':
			decrypt();
			break;
		default:
			printf("\nWrong option...\n");
			return 1;
			break;	// lol
	}

	return 0;
}


