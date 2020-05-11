#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize(const char *buf, size_t bufsize);
int is_valid_char(char c);
void token_add(char c);
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

void tokenize(const char *buf, size_t bufsize) {
	int name_start = 0;
	for (int i=0; i < bufsize; i++) {
		char c = buf[i];
		if (c == '\0') {
			break;
		}

		// TODO: needs proper handling of strings
		if (is_valid_char(c)) {
			if (name_start == 0) {
				name_start = i;
			}
		} else {
			if (name_start > 0) {
				token_add_id(buf, name_start, i);
				name_start = 0;
			}
		}

		if (c == '(') {
			token_add('(');
		} else if (c == ')') {
			token_add(')');
		} else if (c == '"') {
			token_add('"');
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

void token_add(char c) {
	printf("%c", c);
}

void token_add_id(const char *buf, int start, int end) {
	int len = end - start + 1;
	char *t = malloc(sizeof(char) * len);
	strncpy(t, &buf[start], len-1);
	t[len-1] = '\0';
	printf("<%s>", t);
	free(t);
}
