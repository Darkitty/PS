# Parameters for compilation
CC = gcc
SRC = generate.c calculate.c main.c
OBJ = $(SRC: .c=.o)
CFLAGS=-W -Wall -lm -g -O2 -pipe

# SRC variables for moduls
SRC_GEN = generate.c testGenerate.c
SRC_CALC = calculate.c testCalculate.c
SRC_MAIN = generate.c calculate.c main.c


# Main make for final executable
exec: $(OBJ)
	$(CC) -o exec $(OBJ)


# Compilation for Pile and its tests
generate: generate.c testGenerate.c generate.h
	$(CC) -o generate $(SRC_GEN) $(CFLAGS)
# Compilation for List and its tests
calculate: calculate.c testCalculate.c calculate.h
	$(CC) -o calculate $(SRC_CALC) $(CFLAGS)
# Compilation for Cell and its tests
main: generate.c calculate.c main.c generate.h calculate.h
	$(CC) -o main $(SRC_MAIN) $(CFLAGS)


# Utilities
clean:
	rm -f *.o exec* *.exe*

# Generic rules
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)