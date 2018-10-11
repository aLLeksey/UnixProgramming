all: who

who: who.o utmplib.o
	gcc who.o utmplib.o -o who.out

who.o: who.c
	gcc -c who.c

utmplib.o: utmplib.c
	gcc -c utmplib.c


clean:
	rm -rf who.o utmplib.o who.out
