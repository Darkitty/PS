#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>

int generateFile(int nbMult, int x1, int y1, int x2, int y2);
int checkSize(int y1, int x2);