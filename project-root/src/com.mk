CC=gcc
CFLAGS=-Wall -g

SRC=src/tokenizer.c src/matrix.c src/model.c src/main.c
OUT=main.exe

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)
