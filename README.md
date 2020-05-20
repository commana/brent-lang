# Brent-Lang

A small experiment with writing an interpreter for a lisp-like language.

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
op     ::= <name> | <sexpr>
sexpr  ::= '(' <op> <list> ')'
brent  ::= <sexpr> <brent> | e
```

## Abstract Syntax Tree

Here are the first three examples from above shown as an abstract syntax tree (AST).

```
<sexpr>
\
 `<sexpr> ------ <sexpr> ------- <sexpr>
  \              \               \
   `fn --- 43333  `fn --- 0.003   `<sexpr> --- as --- a --- first --- argument
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

