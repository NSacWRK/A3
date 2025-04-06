# Compiler to Use
CC = gcc

# Compiler Flags
CFLAGS = -Wall -std=c99

# Source files
SRC = DB.c DB_impl.c dashboard.c
HEADERS = DB.h DB_impl.h

# Test files
TEST_SRC = Tests/test_DB.c

# Executable names
EXEC = DBExec
TEST_EXEC = DBTest

PACKAGE_NAME = AFVN_as3.tar.gz

# build all
all: $(EXEC) $(TEST_EXEC)

# Main executable
$(EXEC): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $@ 

# Test executable
$(TEST_EXEC): $(TEST_SRC) DB.c DB_impl.c
	$(CC) $(CFLAGS) $^ -o $@ 

# Run test
test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(EXEC) $(TEST_EXEC) *.o

# Create submission tarball
package:
# Create submission directory
	mkdir -p AFVN_as3
	
# Copy all required files
	cp $(SRC) $(HEADERS) makefile README dashboard.c DB_impl.c DB_impl.h DB.c DB.h AFVN_as3/
	
# Copy Tests folder
	cp -r Tests AFVN_as3/
	
# Create tarball
	tar -czvf $(PACKAGE_NAME) AFVN_as3
	
# delete temp directory
	rm -rf AFVN_as3

# phony targets
.PHONY: all clean test package