#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "token.h"

struct brent_symbol_table;
typedef struct brent_symbol_table br_symbol_t;

void br_symbol_insert(br_symbol_t **table, br_token_t type, char *value);
br_symbol_t *  br_symbol_retrieve(br_symbol_t *table, br_token_t type, char *value);
br_symbol_t * br_symbol_create();
void br_symbol_iterate(br_symbol_t *table);

#endif
