/*
 * https://github.com/r4v10l1
 */

#include<stdio.h>

#define MAX_OFFSET 500
#define MAX_MAC_OFFSET 255
#define DEBUG_PRINT 1		// 0 - off

unsigned long offset_from_str(char str[]);
unsigned long mac_from_str(char str[]);
int encrypt();
int decrypt();

/* --------------------------------------------------------------------------- */

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

/* --------------------------------------------------------------------------- */

int encrypt() {
    char filename[100], password[100], c;
    FILE *original_file, *output_file;

    printf("\nFilename: ");
	scanf("%99s", &filename);

	printf("Password: ");
	scanf("%99s", &password);

	// Open input file as read
    original_file = fopen(filename, "r");
    if(original_file == NULL) {
		printf("Error. File does not exist.\n");
        return 1;
	}

	// Open output file as write
    output_file = fopen("encrypted.txt", "w");
    if(output_file == NULL) {	
        return 1;
	}

	// MAC
	fputc( (mac_from_str(password) % MAX_MAC_OFFSET), output_file );
	if (DEBUG_PRINT) {
		printf("MAC: %d\n", (mac_from_str(password) % MAX_MAC_OFFSET));
	}

	// Get each c-haracter of the original file until EOF
    while((c = fgetc(original_file)) != EOF) {
        c = c + ( offset_from_str(password) % MAX_OFFSET );			// We add the offset to enconde our file
        fputc(c, output_file);										// We write the new char to the output file
    }

	// Close the files
    fclose(original_file);
    fclose(output_file);

	printf("Done. Check encrypted.txt\n");
}

/* --------------------------------------------------------------------------- */

int decrypt() {
    char filename[100], password[100], c;
    FILE *original_file, *output_file;

    printf("\nFilename: ");
	scanf("%99s", &filename);

	printf("Password: ");
	scanf("%99s", &password);

	// Open input file as read
    original_file = fopen(filename, "r");
    if(original_file == NULL) {
		printf("Error. File does not exist.\n");
        return 1;
	}

	// Open output file as write
    output_file = fopen("decrypted.txt", "w");
    if(output_file == NULL) {	
        return 1;
	}

	// MAC checking
	c = fgetc(original_file);
	if ( (mac_from_str(password) % MAX_MAC_OFFSET) != c ) {
		if (DEBUG_PRINT) {
			printf("[%d|%d] ", (mac_from_str(password) % MAX_MAC_OFFSET), c);
		}

		printf("Wrong password or invalid file.\n");
		return 1;
	}

	// Get each character of the original file until EOF
    while((c = fgetc(original_file)) != EOF) {
        c = c - ( offset_from_str(password) % MAX_OFFSET );			// We add the offset to enconde our file
        fputc(c, output_file);										// We write the new char to the output file
    }

	// Close the files
    fclose(original_file);
    fclose(output_file);

	printf("Done. Check decrypted.txt\n");
}

/* --------------------------------------------------------------------------- */

unsigned long offset_from_str(char str[]) {
	unsigned long offset = 5381;
	for (int n = 0; str[n] != '\0'; n++) {
		offset = offset * 33 + str[n];
	}
	return offset;
}

/* --------------------------------------------------------------------------- */

unsigned long mac_from_str(char str[]) {
	unsigned long mac = 5381;
	for (int n = 0; str[n] != '\0'; n++) {
		mac = mac + (mac * 33 + str[n]);
	}
	return mac;
}
