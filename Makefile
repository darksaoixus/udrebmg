CC=gcc
CFLAGS=-Wall -Wextra -pedantic
LIB=-L./src/lib -l:libraylib.a -lm
INCLUDE=-I./src/include
src/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LIB) $(INCLUDE)

OBJS = $(wildcard src/*.o)
bin/udrebmg: src/main.c $(OBJS)
	$(CC) $(CFLAGS) -o bin/udrebmg src/main.c $(OBJS) $(LIB) $(INCLUDE)

.PHONY: all clean
clean:
	rm -f src/*.o src/*.gch

all: bin/udrebmg clean

