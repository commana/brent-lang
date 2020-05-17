#ifndef _TOKEN_H_
#define _TOKEN_H_

struct brent_symbol_table;

enum brent_lang_tokens {
	BR_T_ID,
	BR_T_NUMBER,
	BR_T_FLOAT,
	BR_T_STRING,
	BR_T_PAREN_OPEN,
	BR_T_PAREN_CLOSE
};
typedef enum brent_lang_tokens br_token_t;

void tokenize(const char *buf, size_t bufsize, struct brent_symbol_table **sym_table);

#endif
