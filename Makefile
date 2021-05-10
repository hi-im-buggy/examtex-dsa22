CC=gcc
CFLAGS=-Wall
CLIBS=

all: parser interpreter utils list
	$(CC) $(CFLAGS) src/main.c bin/parser.o bin/interpreter.o bin/utils.o bin/list.o $(CLIBS) -o bin/examtex

parser:
	$(CC) -c $(CFLAGS) src/parser.c $(CLIBS) -o bin/parser.o

interpreter:
	$(CC) -c $(CFLAGS) src/interpreter.c $(CLIBS) -o bin/interpreter.o

utils:
	$(CC) -c $(CFLAGS) src/utils.c $(CLIBS) -o bin/utils.o

list:
	$(CC) -c $(CFLAGS) src/list.c $(CLIBS) -o bin/list.o
