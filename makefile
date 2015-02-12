# Parameters for compilation
CC = gcc
SRC = generate.c show.c calculate.c main.c 
OBJ = $(SRC: .c=.o)
CFLAGS=-W -Wall -lm -g -O2 -pipe -lpthread -pedantic -ansi

# SRC variables for moduls
SRC_GEN = generate.c
SRC_SHW = show.c
SRC_CALC = calculate.c testCalculate.c
SRC_MAIN = generate.c show.c calculate.c main.c

# Compilation for Cell and its tests
main: generate.c show.c calculate.c main.c generate.h calculate.h show.h
	$(CC) $(SRC_MAIN) -o main.out $(CFLAGS)

# Compilation for Pile and its tests
generate: generate.c generate.h
	$(CC) -o generate $(SRC_GEN) $(CFLAGS)
# Compilation for Pile and its tests
show: show.c show.h
	$(CC) -o show $(SRC_GEN) $(CFLAGS)
# Compilation for List and its tests
calculate: calculate.c testCalculate.c calculate.h
	$(CC) -o calculate $(SRC_CALC) $(CFLAGS)


# Utilities
clean:
	rm -f *.o exec* *.exe*

# Generic rules
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)