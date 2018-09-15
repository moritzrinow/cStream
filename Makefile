# Sorry for this terrible Makefile. Just started learning Make...

# Compiler options
CC=gcc
CFLAGS=-c -w
LDFLAGS=

# Directories
PROJ=cStream/
SRC=src/
BIN=bin/
OBJ=obj/
INCLUDE=include/

HEADERS_TO_COPY=$(SRC)cStream.h $(SRC)stream.h $(SRC)serialize.h

all: install	

install: create_directories create_libs create_executable copy_headers
	@echo "cStream installed."
	@echo "Include: $(PROJ)$(INCLUDE)"
	@echo "Lib: $(PROJ)$(BIN)libcStream"
	@echo "Test: $(PROJ)$(BIN)test"

create_executable: test
	@echo "Created test executable."

create_libs: libcStream.a
	@echo "Created libraries."

test: test.o libcStream.a
	gcc -o $(BIN)test $(OBJ)test.o $(BIN)libcStream.a -lm

libcStream.a : stream.o serialize.o
	ar rcs $(BIN)libcStream.a $(OBJ)stream.o $(OBJ)serialize.o

test.o: $(SRC)test.c
	gcc $(CFLAGS) $(SRC)test.c -o $(OBJ)test.o

stream.o : $(SRC)stream.c $(SRC)stream.h
	gcc $(CFLAGS) $(SRC)stream.c -o $(OBJ)stream.o

serialize.o: $(SRC)serialize.c $(SRC)serialize.h
	gcc $(CFLAGS) $(SRC)serialize.c -o $(OBJ)serialize.o

create_directories:
	@mkdir -p $(OBJ)
	@mkdir -p $(BIN)
	@mkdir -p $(INCLUDE)
	@echo "Created directories."

copy_headers:
	@cp -f $(HEADERS_TO_COPY) $(INCLUDE)
	@echo "Include directory made."

clean:
	rm -r -f $(BIN) $(OBJ) $(INCLUDE)
	@echo "Cleaned repository."
