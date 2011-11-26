CFLAGS=-Wall -g

.PHONY: clean

all: ex1 ex8 ex9 ex10 ex11 ex12 ex13

clean:
	rm -f ex8
	rm -f ex1
	rm -f ex9
	rm -f ex10
	rm -f ex11
	rm -f ex12
	rm -f ex13
	rm -Rf *.dSYM
