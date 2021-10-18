COMPILE = g++
CFLAGS = -c -Wall


all: develope_mode

develope_mode: main.o stack.o tests.o
	$(COMPILE) main.o stack.o tests.o -o develop_run.exe

main.o: main.cpp
	$(COMPILE) $(CFLAGS) main.cpp

stack.o: stack.cpp
	$(COMPILE) $(CFLAGS) stack.cpp

tests.o: tests.cpp
	$(COMPILE) $(CFLAGS) tests.cpp

clean:
	rm -rf *.o develope_run.exe