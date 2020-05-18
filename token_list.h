#ifndef _TOKEN_LIST_H_
#define _TOKEN_LIST_H_

struct br_token_list_iterator;
typedef struct br_token_list_iterator br_token_iter_t;

br_token_iter_t * token_list_iterator(br_token_list_t *list);
br_token_info_t * token_list_next(br_token_iter_t *iter);
br_token_info_t * token_list_peek(br_token_iter_t *iter);
int token_list_has_next(br_token_iter_t *iter);
void token_list_close_iter(br_token_iter_t *iter);

br_token_list_t * token_list_create();
void token_list_destroy(br_token_list_t *list);

void token_list_insert(br_token_list_t *list, br_token_t token, char *data);
void token_list_iterate(br_token_list_t *list, void (*fn)(br_token_info_t *));

#endif
