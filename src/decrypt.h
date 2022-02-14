
int decrypt() {
	char filename[100], password[100];
	unsigned int c;
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

	/*
	if (c < 0) {
		c = c + MAX_MAC_OFFSET;
	}
	*/

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


