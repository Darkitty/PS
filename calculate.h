#ifndef CALCULATE_H
#define CALCULATE_H

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

/* Structure servant pour passer les donnees aux threads */
typedef struct 
{
	char* adrMap;
	int offset_1;
	int offset_2;
} thread_matrice;

/* Fonction fichier */
char* loadFile();
int getFileSize(const char* file_name);

/* Calcul */
int compute(char* adrMap);

/* Gestion matrice */
void getSize(int* dimMatrice, char* data, int* offset);

float getValue(char * file, int * offset);

void nextValue(char* file, int* offset);
void nextColumn(char* file, int* offset, int x);
int getRelativeOffset(char * fmap, int offset, int x);
void pastLine(char* file, int* offset, int x);

#endif