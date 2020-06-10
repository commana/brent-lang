# Brent-Lang

A small experiment with writing an interpreter/compiler for a lisp-like language.

## Example

```scheme
; a full line comment

(fn 43333) ; a partial line comment

(fn 0.003) ; arbitrary precision numbers

((apply (a (list))) as first argument)

(define brentarus 42)

(define greeting "Hello, World!")

(
	this is a
	(multi line)
	; :o
	(list)
)
```

## Grammar

```
string ::= '"' [^\"\v]* '"'
num    ::= [0-9]+ ( '.' [0-9]+ )?
number ::= <num> | '-' <num>
name   ::= [A-Za-z] [A-Za-z0-9\-\?\!]*
atom   ::= <name> | <number> | <string>
list   ::= <atom> <list> | <sexpr> <list> | e
sexpr  ::= '(' <list> ')'
brent  ::= <sexpr> <brent> | e
```

### FIRST set
```
FIRST(number) = { [0-9], - }
FIRST(atom)   = { [A-Za-z], " } U FIRST(number)
FIRST(list)   = { e } U FIRST(atom) U FIRST(sexpr)
FIRST(sexpr)  = { ( }
FIRST(brent)  = { e } U FIRST(sexpr)
```

### FOLLOW set
```
FOLLOW(atom)  = FIRST(atom) U FIRST(sexpr) U FOLLOW(list)
FOLLOW(list)  = { ) }
FOLLOW(sexpr) = FOLLOW(brent)
FOLLOW(brent) = { (, $ }
```

## Abstract Syntax Tree

Here are the first three examples from above shown as an abstract syntax tree (AST).

```
<sexpr>
\
 `<sexpr> ------ <sexpr> ------- <sexpr>
  \              \               \
   `fn --- 43333  `fn --- 0.003   `<sexpr> --- as --- first --- argument
                                   \
                                    `apply --- <sexpr>
                                               \
                                                `a --- <sexpr>
                                                       \
                                                        `list
```

## Todos

- [ ] Tokenize
  - [ ] Error messages
  - [ ] Symbol table
- [ ] Parse
  - [ ] Error messages
  - [ ] Abstract Syntax Tree
  - [ ] Print AST similar to example above
- [ ] Evaluate
- [ ] Compile to C
