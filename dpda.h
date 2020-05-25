#ifndef _DPDA_H_
#define _DPDA_H_

#include "token.h"
#include "token_list.h"
#include "ast.h"

struct brent_lang_dpda;
typedef struct brent_lang_dpda br_dpda_t;

br_dpda_t * dpda_create();
void dpda_destroy(br_dpda_t *dpda);

void dpda_transition(br_dpda_t *dpda, br_token_list_t *input,  br_sexpr_t *ast);
br_token_t dpda_pop(br_dpda_t *dpda);
void dpda_push(br_dpda_t *dpda, br_token_t elem);
int dpda_is_empty(br_dpda_t *dpda);

#endif
