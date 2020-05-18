#include <stdio.h>
#include <stdlib.h>

#include "dpda.h"

struct brent_lang_dpda {
	int size;
	int pos; // points to the next free slot, so the stack actually starts at pos-1
	br_token_t *stack;
};

br_dpda_t * dpda_create() {
	br_dpda_t *dpda = malloc(sizeof(br_dpda_t));
	dpda->size = 256;
	dpda->pos = 0;
	dpda->stack = malloc(dpda->size * sizeof(br_token_t));
	for (int i=0; i < dpda->size; i++) {
		dpda->stack[i] = -1;
	}
	dpda_push(dpda, BR_N_BRENT); // initialize stack for our language
	return dpda;
}

void dpda_destroy(br_dpda_t *dpda) {
	free(dpda->stack);
	free(dpda);
}

void dpda_push(br_dpda_t *dpda, br_token_t elem) {
	// TODO: dynamically resize stack
	dpda->stack[dpda->pos++] = elem;
}

br_token_t dpda_pop(br_dpda_t *dpda) {
	if (dpda_is_empty(dpda)) {
		fprintf(stderr, "Error: stack is empty\n");
		exit(-1);
	}
	br_token_t head = dpda->stack[dpda->pos-1];
	dpda->pos--;
	return head;
}

int dpda_is_empty(br_dpda_t *dpda) {
	return dpda->pos == 0;
}

void dpda_transition(br_dpda_t *dpda, br_token_list_t *list, void *output) {
	br_token_iter_t *iter = token_list_iterator(list);
	while (!dpda_is_empty(dpda)) {
		br_token_t stack = dpda_pop(dpda);
		if (!token_list_has_next(iter) && stack == BR_N_BRENT) {
			// apply epsilon rule for <brent> and exit
			break;
		}
		br_token_info_t *input = token_list_peek(iter);
		// check terminals first (<100), then non-terminals (>=100), see token.h for numbers
		if (stack < 100) {
			if (stack == input->type) {
				// consume (and throw away) element
				token_list_next(iter);
			} else {
				fprintf(stderr, "Syntax error: expected <%d>, found '%s'\n", stack, input->content);
				break;
			}
		} else {
			// Non-terminals
			switch (stack) {
				case BR_N_BRENT:
					if (token_list_has_next(iter)) {
						dpda_push(dpda, BR_N_BRENT);
						dpda_push(dpda, BR_N_SEXPR);
					} else {
						// epsilon rule in <brent>
					}
					break;
				case BR_N_SEXPR:
					dpda_push(dpda, BR_T_PAREN_CLOSE);
					dpda_push(dpda, BR_N_LIST);
					dpda_push(dpda, BR_N_OP);
					dpda_push(dpda, BR_T_PAREN_OPEN);
					break;
				case BR_N_OP:
					switch (input->type) {
						case BR_T_ID:
							dpda_push(dpda, BR_T_ID);
							break;
						case BR_T_PAREN_OPEN:
							dpda_push(dpda, BR_N_SEXPR);
							break;
						default:
							fprintf(stderr, "Syntax error at input %s\n", input->content);
							break;
					}
					break;		
				case BR_N_LIST:
					switch (input->type) {
						case BR_T_NUMBER:
						case BR_T_FLOAT:
						case BR_T_STRING:
						case BR_T_ID:
							dpda_push(dpda, BR_N_LIST);
							dpda_push(dpda, BR_N_ATOM);
							break;
						case BR_T_PAREN_OPEN:
							dpda_push(dpda, BR_N_LIST);
							dpda_push(dpda, BR_N_SEXPR);
							break;
						case BR_T_PAREN_CLOSE:
							// epsilon rule in <list>
							break;
						default:
							fprintf(stderr, "Syntax error at input %s\n", input->content);
							break;
					}
					break;
				case BR_N_ATOM:
					switch (input->type) {
						case BR_T_ID:
							dpda_push(dpda, BR_T_ID);
							break;
						case BR_T_NUMBER:
							dpda_push(dpda, BR_T_NUMBER);
							break;
						case BR_T_FLOAT:
							dpda_push(dpda, BR_T_FLOAT);
							break;
						case BR_T_STRING:
							dpda_push(dpda, BR_T_STRING);
							break;
						default:
							fprintf(stderr, "Syntax error at input %s\n", input->content);
							break;
					}
					break;
				default:
					fprintf(stderr, "Syntax error at input %s\n", input->content);
					break;
			}
		}
	}
	if (token_list_has_next(iter)) {
		fprintf(stderr, "Found unexpected input after end of syntax analysis\n");
	}
	token_list_close_iter(iter);
}
