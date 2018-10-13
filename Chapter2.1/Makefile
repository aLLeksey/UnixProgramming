all: who

who: who3.o utmplib.o logout_tty.o
	gcc who3.o utmplib.o logout_tty.o -o who.out

who3.o: who3.c
	gcc -c who3.c

utmplib.o: utmplib.c
	gcc -c utmplib.c

logout_tty.o: logout_tty.c
	gcc -c logout_tty.c

clean:
	rm -rf who.o utmplib.o who.out
