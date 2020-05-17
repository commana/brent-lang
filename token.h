#ifndef _TOKEN_H_
#define _TOKEN_H_

enum brent_lang_tokens {
	BR_T_ID,
	BR_T_NUMBER,
	BR_T_FLOAT,
	BR_T_STRING,
	BR_T_PAREN_OPEN,
	BR_T_PAREN_CLOSE
};
typedef enum brent_lang_tokens br_token_t;

struct brent_lang_token_info {
	br_token_t type;
	char *content;
};
typedef struct brent_lang_token_info br_token_info_t;

struct br_token_list;
typedef struct br_token_list br_token_list_t;

void tokenize(const char *buf, size_t bufsize, br_token_list_t *list);

#endif
