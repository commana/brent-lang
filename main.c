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
	BR_STATE_ATOM,
	BR_STATE_NAME,
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

int is_number(char c) {
	return is_digit(c);
}

int is_paren_open(char c) {
	return c == '(';
}

int is_paren_close(char c) {
	return c == ')';
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

int is_char(char c) {
	return is_uppercase(c) || is_lowercase(c);
}

int is_char_ext(char c) {
	return is_char(c) || is_digit(c) || c == '-' || c == '?' || c == '!';
}

int is_string(char c) {
	return c == '"';
}

int is_atom(char c) {
	return is_char(c) || is_digit(c) || is_string(c);
}

void tokenize(const char *buf, size_t bufsize) {
	static br_state_t state = BR_STATE_INIT;
	static int line = 0;
	int start = 0;
	for (int i=0; i < bufsize; i++) {
		char c = buf[i];
		if (c == '\0') {
			break;
		}

		switch (state) {
			case BR_STATE_INIT:
				if (is_line_comment(c)) {
					state = BR_STATE_LINE_COMMENT;
					break;
				}
				if (is_paren_open(c)) {
					token_add(BR_T_PAREN_OPEN);
					break;
				}
				if (is_paren_close(c)) {
					token_add(BR_T_PAREN_CLOSE);
					break;
				}
				if (is_atom(c)) {
					state = BR_STATE_ATOM;
					i--;
				}
				break;
			case BR_STATE_ATOM:
				if (is_char(c)) {
					state = BR_STATE_NAME;
				} else if (is_number(c) || c == '-') {
					state = BR_STATE_NUM;
				} else if (is_string(c)) {
					state = BR_STATE_STRING;
				} else {
					fprintf(stderr, "Unexpected char %c\n", c);
					exit(-1);
				}
				start = i; // begin consuming the element
				break;
			case BR_STATE_NAME:
				if (is_char_ext(c)) {
					state = BR_STATE_NAME;
				} else {
					token_add_id(buf, start, i);
					state = BR_STATE_INIT;
					i--; // do not consume this char
				}
				break;
			case BR_STATE_NUM:
				if (is_digit(c)) {
					state = BR_STATE_NUM;
				} else if (c == '.') {
					state = BR_STATE_NUM_FLOAT;
				} else {
					token_add_id(buf, start, i);
					state = BR_STATE_INIT;
					i--; // do not consume this char
				}
				break;
			case BR_STATE_NUM_FLOAT:
				if (is_digit(c)) {
					break;
				} else {
					token_add_id(buf, start, i);
					state = BR_STATE_INIT;
					i--; // do not consume this char
				}
				break;
			case BR_STATE_STRING:
				if (is_string(c)) {
					token_add_id(buf, start, i+1);
					state = BR_STATE_INIT;
					break;
				} else if (is_newline(c)) {
					fprintf(stderr, "Unterminated string on line %d\n", line);
					exit(-1);
				}
				break;
			case BR_STATE_LINE_COMMENT:
				if (is_newline(c)) {
					line++;
					state = BR_STATE_INIT;
				}
				break;
			default:
				printf("Unknown scanner state: %d\n", state);
				break;
		}
	}
}

int is_valid_char(char c) {
	return 0; 
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
