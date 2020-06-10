#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

enum content_type {
	BR_CT_BRENT,
	BR_CT_SEXPR,
	BR_CT_ID,
	BR_CT_INT,
	BR_CT_FLOAT,
	BR_CT_STRING
};

struct br_lang_sexpr {
	br_sexpr_t *parent;
	br_sexpr_t *first_child;
	br_sexpr_t *next_sibling;
	enum content_type type;
	union content {
		int int_number;
		float float_number;
		char *string;
	} node_content;
};

br_sexpr_t * ast_find_last_sibling(br_sexpr_t *node);

void ast_add_child(br_sexpr_t *tree, br_sexpr_t *node) {
	if (tree->first_child == NULL) {
		tree->first_child = node;
		node->parent = tree;
		return;
	}
	// add node to the last sibling
	br_sexpr_t *last_sibling = ast_find_last_sibling(tree->first_child);
	last_sibling->next_sibling = node;
	node->parent = tree;
}

br_sexpr_t * ast_find_last_sibling(br_sexpr_t *node) {
	if (node->next_sibling == NULL) {
		return node;
	}
	return ast_find_last_sibling(node->next_sibling);
}

br_sexpr_t * ast_create() {
	return calloc(1, sizeof(br_sexpr_t));
}

br_sexpr_t * ast_create_root() {
	br_sexpr_t *node = ast_create();
	node->type = BR_CT_BRENT;
	return node;
}

br_sexpr_t * ast_create_sexpr() {
	br_sexpr_t *node = ast_create();
	node->type = BR_CT_SEXPR;
	return node;
}

br_sexpr_t * ast_create_int(int value) {
	br_sexpr_t *node = ast_create();
	node->type = BR_CT_INT;
	node->node_content.int_number = value;
	return node;
}

br_sexpr_t * ast_create_float(float value) {
	br_sexpr_t *node = ast_create();
	node->type = BR_CT_FLOAT;
	node->node_content.float_number = value;
	return node;
}

br_sexpr_t * ast_create_string(char *value) {
	br_sexpr_t *node = ast_create();
	node->type = BR_CT_STRING;
	node->node_content.string = value;
	return node;
}

br_sexpr_t * ast_create_id(char *value) {
	br_sexpr_t *node = ast_create();
	node->type = BR_CT_ID;
	node->node_content.string = value;
	return node;
}

br_sexpr_t * ast_get_parent(const br_sexpr_t *node) {
	return node->parent;
}

void ast_print(br_sexpr_t *ast, char *buffer) {
	if (ast->type == BR_CT_BRENT) {
		sprintf(buffer, ".");
	} else if (ast->type == BR_CT_SEXPR) {
		sprintf(buffer, "%s <sexpr>", buffer);
	} else {
		sprintf(buffer, "%s %d", buffer, ast->type);
	}
	if (ast->first_child != NULL) {
		sprintf(buffer, "%s [", buffer);
		ast_print(ast->first_child, buffer);
		sprintf(buffer, "%s ]", buffer);
	}

	if (ast->next_sibling != NULL) {
		sprintf(buffer, "%s ---", buffer);
		ast_print(ast->next_sibling, buffer);
	}
}

