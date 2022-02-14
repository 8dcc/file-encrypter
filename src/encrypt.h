
int encrypt() {
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

