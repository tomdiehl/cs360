
#################################################
#   makefile for tiny shell
#################################################

### settings ...

CFLAGS = 
OBJ = exec.o get.o main.o misc.o parse.o prog.o redirect.o

### primary rules ...

tsh : $(OBJ)
	cc $(CFLAGS) -o tsh $(OBJ)

clean :
	rm -f tsh *.o
	touch tsh.h

expected : tsh testfile
	tsh -e < testfile > expected 2>&1
	
actual : tsh testfile expected
	tsh -e < testfile > actual 2>&1
	diff actual expected

install : tsh
	cp tsh /net/class/cs360/bin
	mkdir -p /net/class/cs360/src/tsh
	cp makefile *.h *.c /net/class/cs360/src/tsh

### secondary rules ...

$(OBJ) : tsh.h
