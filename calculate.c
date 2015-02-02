#include "calculate.h"

int calculMatrice(const char* file) {
	FILE *fp;
	int* x;
	x = malloc(sizeof(int));

	fp = fopen(file,"r");
	while(fscanf(fp,"%d",x) == 1)  
	{
		printf("\n%d", *x);  
	}

	return 0;
}