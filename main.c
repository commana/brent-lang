#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum brent_lang_tokens {
	BR_T_ID,
	BR_T_PAREN_OPEN,
	BR_T_PAREN_CLOSE
};
typedef enum brent_lang_tokens br_token_t;

enum brent_lang_token_states {
	BR_STATE_INIT,
	BR_STATE_ID,
	BR_STATE_NUM,
	BR_STATE_NUM_FLOAT,
	BR_STATE_LINE_COMMENT,
	BR_STATE_STRING,
	BR_STATE_ERROR
};
typedef enum brent_lang_token_states br_state_t;

void tokenize(const char *buf, size_t bufsize);
int is_valid_char(char c);
void token_add(br_token_t token);
void token_add_id(const char *buf, int start, int end);

int main(int argc, char **argv) {
	FILE *src = fopen(argv[1], "r");

	char buf[256];
	while(!feof(src)) {
		int c = fread(&buf, sizeof(char), sizeof(buf) - 1, src);
		buf[c] = '\0';
		tokenize(buf, sizeof(buf));
	}

	fclose(src);
	return 0;
}

int is_whitespace(char c) {
	return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}

int is_digit(char c) {
	return c >= 48 && c <= 57;
}

int is_digit_with_dot(char c) {
	return is_digit(c) || c == '.';
}

int is_paren_open(char c) {
	return c == '(';
}

int is_paren_close(char c) {
	return c == ')';
}

int is_id(char c) {
	return is_valid_char(c);
}

int is_line_comment(char c) {
	return c == ';';
}

int is_comment(char c) {
	return is_line_comment(c);
}

int is_newline(char c) {
	return c == '\n';
}

int is_uppercase(char c) {
	return (c >= 65 && c <= 90);
}

int is_lowercase(char c) {
	return (c >= 97 && c <= 122);
}

int is_operator(char c) {
	return c == '-'
		;
}

int is_id_start(char c) {
	return is_uppercase(c) || is_lowercase(c) || is_operator(c);
}

int is_paren(char c) {
	return is_paren_open(c) || is_paren_close(c);
}

int is_string(char c) {
	return c == '"';
}

int is_breaker(char c) {
	return is_paren(c) || is_comment(c) || is_whitespace(c);
}

int is_dot(char c) {
	return c == '.';
}

void handle_breaker(char c, br_state_t *state) {
	*state = BR_STATE_INIT; // set default state
	if (is_paren_open(c)) {
		token_add(BR_T_PAREN_OPEN);
	}
	if (is_paren_close(c)) {
		token_add(BR_T_PAREN_CLOSE);
	}
	if (is_line_comment(c)) {
		*state = BR_STATE_LINE_COMMENT;
	}
}

void tokenize(const char *buf, size_t bufsize) {
	static br_state_t state = BR_STATE_INIT;
	int start = 0;
	for (int i=0; i < bufsize; i++) {
		char c = buf[i];
		if (c == '\0') {
			break;
		}

		switch (state) {
			case BR_STATE_INIT:
				if (is_paren_open(c)) {
					token_add(BR_T_PAREN_OPEN);
				} else if (is_paren_close(c)) {
					token_add(BR_T_PAREN_CLOSE);
				} else 	if (is_digit(c)) {
					state = BR_STATE_NUM;
					start = i;
				} else if (is_id_start(c)) {
					state = BR_STATE_ID;
					start = i;
				} else 	if (is_string(c)) {
					state = BR_STATE_STRING;
					start = i;
				} else if (is_line_comment(c)) {
					state = BR_STATE_LINE_COMMENT;
				} else if (is_whitespace(c)) {
					;
				} else {
					printf("Unknown char encountered: %c\n", c);
					state = BR_STATE_ERROR;
				}
				break;
			case BR_STATE_NUM:
				if (is_dot(c)) {
					state = BR_STATE_NUM_FLOAT;
					break;
				}
				if (is_digit(c)) break;

				if (is_breaker(c)) {
					token_add_id(buf, start, i);
					handle_breaker(c, &state);
					break;
				} else {
					printf("Invalid character: %c\n", c);
					state = BR_STATE_ERROR;
				}
				break;
			case BR_STATE_NUM_FLOAT:
				if (is_digit(c)) break;
				
				if (is_breaker(c)) {
					token_add_id(buf, start, i);
					handle_breaker(c, &state);
					break;
				} else {
					printf("Invalid character: %c\n", c);
					state = BR_STATE_ERROR;
				}
				break;
			case BR_STATE_ID:
				if (is_valid_char(c)) break;

				if (is_breaker(c)) {
					token_add_id(buf, start, i);
					handle_breaker(c, &state);
				} else {
					printf("Invalid character: %c\n:", c);
					state = BR_STATE_ERROR;
				}
				break;
			case BR_STATE_STRING:
				if (!is_string(c)) break;

				token_add_id(buf, start, i+1); // add closing quotation mark
				handle_breaker(c, &state);
				break;
			case BR_STATE_LINE_COMMENT:
				if (is_newline(c)) {
					state = BR_STATE_INIT;
				}
				break;
			case BR_STATE_ERROR:
				exit(-1);
			default:
				printf("Unknown scanner state: %d\n", state);
				break;
		}
	}
}

int is_valid_char(char c) {
	return is_id_start(c) || is_digit(c);
}

void token_add(br_token_t token) {
	printf("%d", token);
}

void token_add_id(const char *buf, int start, int end) {
	int len = end - start + 1;
	char *t = malloc(sizeof(char) * len);
	strncpy(t, &buf[start], len-1);
	t[len-1] = '\0';
	printf("<%s>", t);
	free(t);
}
