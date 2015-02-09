#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <time.h>

int generateFile(int nbMult);
void generateMatrice(FILE* file, int x, int y);