#ifndef _AST_H_
#define _AST_H_

struct br_lang_sexpr;
typedef struct br_lang_sexpr br_sexpr_t;

br_sexpr_t * ast_create_root();
br_sexpr_t * ast_create_sexpr();
br_sexpr_t * ast_create_int(int value);
br_sexpr_t * ast_create_float(float value);
br_sexpr_t * ast_create_string(char *value);
br_sexpr_t * ast_create_id(char *value);

br_sexpr_t * ast_get_parent(const br_sexpr_t *node);
void ast_add_child(br_sexpr_t *parent, br_sexpr_t *node);

void ast_print(br_sexpr_t *ast, char *buffer);

#endif
