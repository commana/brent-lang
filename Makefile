CC=gcc
CFLAGS=
DEPS=

LIBS=
OBJ=main.o symbol.o token.o token_list.o dpda.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

brent: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o 
