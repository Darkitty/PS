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

char* loadFile(const char* file);
int compute(char* adrMap);
char* getSize(int* nbMatrice, char* data);
float** initMatrice(float*** matrice, int x, int y);
char* getMatrice(char* data, float** matrice, int x, int y);
void freeMatrice(float** matrice, int x);