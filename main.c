#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum brent_lang_tokens {
	BR_T_WHITESPACE,
	BR_T_ID,
	BR_T_PAREN_OPEN,
	BR_T_PAREN_CLOSE
};
typedef enum brent_lang_tokens br_token_t;

enum brent_lang_token_states {
	BR_STATE_INIT,
	BR_STATE_WHITESPACE,
	BR_STATE_ID,
	BR_STATE_NUM
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

int is_paren_open(char c) {
	return c == '(';
}

int is_paren_close(char c) {
	return c == ')';
}

int is_id(char c) {
	return is_valid_char(c);
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
				if (is_digit(c)) {
					state = BR_STATE_NUM;
					start = i;
				}
				if (is_paren_open(c)) {
					token_add(BR_T_PAREN_OPEN);
				}
				if (is_paren_close(c)) {
					token_add(BR_T_PAREN_CLOSE);
				}
				if (is_whitespace(c)) {
					state = BR_STATE_WHITESPACE;
					token_add(BR_T_WHITESPACE);
				}
				break;
			case BR_STATE_NUM:
				if (is_digit(c)) break;

				token_add_id(buf, start, i);
				if (is_whitespace(c)) {
					state = BR_STATE_WHITESPACE;
					token_add(BR_T_WHITESPACE);
				}
				if (is_paren_open(c)) {
					state = BR_STATE_INIT;
					token_add(BR_T_PAREN_OPEN);
				}
				if (is_paren_close(c)) {
					state = BR_STATE_INIT;
					token_add(BR_T_PAREN_CLOSE);
				}
				break;
			case BR_STATE_WHITESPACE:
				if (is_digit(c)) {
					state = BR_STATE_NUM;
					start = i;
				}
				break;
			default:
				printf("Unknown scanner state: %d\n", state);
				break;
		}
	}
}

int is_valid_char(char c) {
	return (c >= 48 && c <= 57) // 0-9
		|| (c >= 65 && c <= 90) // A-Z
		|| (c >= 97 && c <= 122) // a-z
		|| (c == 45) // '-'
		;
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
