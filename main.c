#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "token_list.h"

int main(int argc, char **argv) {
	FILE *src = fopen(argv[1], "r");

	br_token_list_t *list = token_list_create();
	char buf[256];
	while(!feof(src)) {
		int c = fread(&buf, sizeof(char), sizeof(buf) - 1, src);
		buf[c] = '\0';
		tokenize(buf, sizeof(buf), list);
	}
	token_list_iterate(list);

	fclose(src);
	return 0;
}
