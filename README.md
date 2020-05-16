# Brent-Lang

A small experiment with writing an interpreter for a lisp-like language.

Example:

```scheme
; code.br
(define name "Brentarus")

(print name)
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

