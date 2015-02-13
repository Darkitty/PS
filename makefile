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

# Compilation for main executable
main: generate.c show.c calculate.c main.c generate.h calculate.h show.h define.h
	$(CC) $(SRC_MAIN) -o main.out $(CFLAGS)

# Compilation generate
generate: generate.c generate.h define.h
	$(CC) -o generate $(SRC_GEN) $(CFLAGS)
# Compilation show
show: show.c show.h define.h
	$(CC) -o show $(SRC_GEN) $(CFLAGS)
# Compilation calculate
calculate: calculate.c testCalculate.c calculate.h define.h
	$(CC) -o calculate $(SRC_CALC) $(CFLAGS)


# Utilities
clean:
	rm -f *.o exec* *.exe*

# Generic rules
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)