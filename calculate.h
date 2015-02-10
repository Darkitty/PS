#define _GNU_SOURCE
#include <pthread.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>

typedef struct 
{
	char* adrMap;
	int offset_1;
	int offset_2;
} thread_matrice;

char* loadFile(const char* file);
int compute(char* adrMap);
void getSize(int* dimMatrice, char* data, int* offset);
float** initMatrice(float*** matrice, int x, int y);
char* getMatrice(char* data, float** matrice, int x, int y);
void freeMatrice(float** matrice, int x);

float getValue(char * file, int * offset);
void pastLine(char* file, int* offset, int x);
void nextColumn(char* file, int* offset, int x);

int getRelativeOffset(char * fmap, int offset, int n);

void nextNbLines(char * fmap, int * offset, int nblines);

void nextValue(char* file, int* offset);