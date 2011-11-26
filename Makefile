CFLAGS=-Wall -g

.PHONY: clean commit

all: ex1 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15

clean:
	rm -f ex8
	rm -f ex1
	rm -f ex9
	rm -f ex10
	rm -f ex11
	rm -f ex12
	rm -f ex13
	rm -f ex14
	rm -f ex15
	rm -Rf *.dSYM

#Figure out how to pass a command line variable into a make target
commit: clean $(MESSAGE)
	git commit -am "$(MESSAGE)"
