CC=gcc
CFLAGS=-I.
OUTFILE=archtrain
SRC=main.c
all:
	$(CC) $(SRC) -o $(OUTFILE) $(CFLAGS)

