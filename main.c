#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "token_list.h"
#include "dpda.h"
#include "ast.h"

void print(br_token_info_t *t) {
	printf("<%d,%s>", t->type, t->content);
}

void parse(br_token_list_t *list) {
	token_list_iterate(list, &print);
	printf("\n");

	br_dpda_t *dpda = dpda_create();
	br_sexpr_t *ast = ast_create_root();
	dpda_transition(dpda, list, ast);
	dpda_destroy(dpda);

	char buffer[1024] = { 0 }; // TODO: may get out of bounds
	ast_print(ast, buffer);
	fprintf(stdout, "%s\n", buffer);
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
