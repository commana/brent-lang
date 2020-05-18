#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "token_list.h"
#include "dpda.h"

void print(br_token_info_t *t) {
	printf("<%d,%s>", t->type, t->content);
}

void parse(br_token_list_t *list) {
	token_list_iterate(list, &print);
	printf("\n");

	br_dpda_t *dpda = dpda_create();
	dpda_transition(dpda, list, NULL);
	dpda_destroy(dpda);
}

int main(int argc, char **argv) {
	FILE *src = fopen(argv[1], "r");

	br_token_list_t *list = token_list_create();
	char buf[256];
	while(!feof(src)) {
		int c = fread(&buf, sizeof(char), sizeof(buf) - 1, src);
		buf[c] = '\0';
		tokenize(buf, sizeof(buf), list);
	}
	parse(list);

	token_list_destroy(list);
	fclose(src);
	return 0;
}
