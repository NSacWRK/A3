# Compiler to Use
CC = gcc
# Compiler Flags
CFLAGS = -Wall -std=c99
# Name of the Package to Create
PACKAGE_NAME = cmpt201_A3_.tar.gz
# Source Files Pattern (expansion for .c files)
SRC = DB.c DB.h

DBExec: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -f DBExec A3
