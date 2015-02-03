#define _GNU_SOURCE
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>

int intMatrice(const char* file, int** matrice1, int** matrice2);
int compute(int** matrice1, int** matrice2);