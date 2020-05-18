#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "token_list.h"

struct br_token_list {
	int index;
	int size;

	br_token_info_t **contents;
};

br_token_list_t * token_list_create() {
	br_token_list_t *ll = malloc(sizeof(br_token_list_t));
	ll->size = 256;
	ll->index = 0;
	
	br_token_info_t **array = malloc(ll->size * sizeof(br_token_info_t*));
	for (int i=0; i < ll->size; i++) {
		array[i] = NULL;
	}
	ll->contents = array;
	return ll;
}

void token_list_insert(br_token_list_t *list, br_token_t token, char *data) {
	// TODO: check if full
	br_token_info_t *info = malloc(sizeof(br_token_info_t));
	info->type = token;
	info->content = data;
	list->contents[list->index++] = info;
}

void token_list_iterate(br_token_list_t *list, void (*fn)(br_token_info_t *)) {
	for (int i=0; i < list->index; i++) {
		br_token_info_t *t = list->contents[i];
		if (t != NULL) {
			(*fn)(t);
		}
	}
}

void token_list_destroy(br_token_list_t *list) {
	for (int i=0; i < list->size; i++) {
		br_token_info_t *t = list->contents[i];
		if (t != NULL) {
			free(t->content);
			free(t);
		}
	}
	free(list);
}
