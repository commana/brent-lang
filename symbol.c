#include <stdlib.h>
#include <string.h>

#include "symbol.h"
#include "token.h"

struct brent_symbol_table {
	struct brent_symbol_table_entry {
		br_token_t token;
		char *name;
	} value;
	br_symbol_t *next;
};

br_symbol_t * br_symbol_create() {
	return NULL; 
}

void br_symbol_insert(br_symbol_t **table, br_token_t type, char *value) {
	br_symbol_t *e = malloc(sizeof(br_symbol_t));
	e->value.token = type;
	e->value.name = malloc(strlen(value) + 1);
	strcpy(e->value.name, value);
	e->next = *table;

	*table = e;
}

br_symbol_t *  br_symbol_retrieve(br_symbol_t *table, br_token_t type, char *value) {
	if (table == NULL) {
		return NULL;
	}

	struct brent_symbol_table_entry e = table->value;
	if (e.token == type && strcmp(e.name, value) == 0) {
		return table;
	}
	return br_symbol_retrieve(table->next, type, value);
}
