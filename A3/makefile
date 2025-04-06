# Compiler to Use
CC = gcc
# Compiler Flags
CFLAGS = -Wall -std=c99
# Name of the Package to Create
PACKAGE_NAME = AFVN_as3.tar.gz
# Source Files Pattern (expansion for .c files)
SRC = DB.c DB.h

DBExec: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

DBTest: Tests/testDB.c DB.c DB_impl.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

testingFunctionExec: 
	./DBTest

clean:
	rm -f DBExec A3

package:
	tar -czvf $(PACKAGE_NAME) $(SRC) makefile README Tests DB_impl.h DB_impl.c dashboard.c
