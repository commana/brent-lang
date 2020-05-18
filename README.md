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

; these will fail:
; (42.xyz)
; (42xyz)
; (: x y)
; (yolo:23) ; might allow this in the future
; ("no closing quotation mark

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

## Todos

- [ ] Tokenize
  - [ ] Error messages
  - [ ] Symbol table
- [ ] Parse
  - [ ] Error messages
  - [ ] Abstract Syntax Tree
- [ ] Evaluate

