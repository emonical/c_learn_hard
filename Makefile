CFLAGS=-Wall -g

.PHONY: clean commit

TARGETS=ex1 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16

all: $(TARGETS)

clean:
	rm -f $(TARGETS)	
	rm -Rf *.dSYM

#Figure out how to pass a command line variable into a make target
commit: clean $(MESSAGE)
	git commit -am "$(MESSAGE)"
