#ifndef _TOKEN_LIST_H_
#define _TOKEN_LIST_H_

br_token_list_t * token_list_create();
void token_list_insert(br_token_list_t *list, br_token_t token, char *data);
void token_list_iterate(br_token_list_t *list);
void token_list_destroy(br_token_list_t *list);

#endif
