COPTS = -std=c99 -Wall -pedantic -c
GET_WORD =/encs_share/cs/class/cs360

JUNK = *.o *~
ALL = Wordpairs

all:$(ALL)

clean:
	-rm -rf $(JUNK)

Wordpairs: main.o hash.o
	gcc -g -L ${GET_WORD}/lib main.o hash.o -o wordpairs -lget

main.o: hash.c hash.h main.c
	gcc ${COPTS} -I ${GET_WORD}/include main.c

hash.o: hash.c hash.h
	gcc ${COPTS} hash.c


