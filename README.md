# Brent-Lang

A small experiment with writing an interpreter for a lisp-like language.

Example:

```scheme
; code.br
; a full line comment
(42 43333) ; a partial line comment
(42.42 0.003) ; arbitrary precision numbers

(define brentarus 42)
(define greeting "Hello, World!")

(
	this is a
	(multi line)
	; :o
	(list)
)
```
# Grammar

```
string ::= '"' [^\"\v]* '"'
num    ::= [0-9]+ ( '.' [0-9]+ )?
number ::= <num> | '-' <num>
name   ::= [A-Za-z] [A-Za-z0-9\-\?\!]*
atom   ::= <name> | <number> | <string>
list   ::= <atom> | <sexpr> | e
sexpr  ::= '(' <list> ')'
brent  ::= <sexpr>*
```

Todos:

- [ ] Tokenize
  - [ ] Error messages
  - [ ] Symbol table
- [ ] Parse
- [ ] Evaluate

