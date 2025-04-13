# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -lm

# Source files and output
SRC = src/tokenizer.c src/matrix.c src/model.c src/main.c
OUT = main.exe

# Default target
all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

# Clean target to remove the executable
clean:
	rm -f $(OUT)