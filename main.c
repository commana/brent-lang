#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "symbol.h"


int main(int argc, char **argv) {
	FILE *src = fopen(argv[1], "r");

	br_symbol_t *table = br_symbol_create();
	char buf[256];
	while(!feof(src)) {
		int c = fread(&buf, sizeof(char), sizeof(buf) - 1, src);
		buf[c] = '\0';
		tokenize(buf, sizeof(buf), &table);
	}
	br_symbol_iterate(table);

	fclose(src);
	return 0;
}
