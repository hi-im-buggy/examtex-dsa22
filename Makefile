CC=gcc
CFLAGS=-Wall
CLIBS=

all: parser interpreter
	$(CC) $(CFLAGS) src/main.c bin/parser.o bin/interpreter.o bin/utils.o bin/list.o $(CLIBS) -o bin/examtex

parser: utils
	$(CC) -c $(CFLAGS) src/parser.c bin/utils.o bin/list.o $(CLIBS) -o bin/parser.o

interpreter: utils
	$(CC) -c $(CFLAGS) src/interpreter.c bin/utils.o bin/list.o $(CLIBS) -o bin/interpreter.o

utils: list
	$(CC) -c $(CFLAGS) src/utils.c bin/list.o $(CLIBS) -o bin/utils.o

list:
	$(CC) -c $(CFLAGS) src/list.c $(CLIBS) -o bin/list.o
