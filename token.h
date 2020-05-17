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

#endif
