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
