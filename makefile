CC=gcc
CFLAGS=-I./include
OUTFILE=./dist/archtrain
SRC=./src/
all:
	$(CC) $(SRC)*.c -o $(OUTFILE) $(CFLAGS)

