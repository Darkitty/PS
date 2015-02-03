#include "calculate.h"

int intMatrice(const char* file, int** matrice1, int** matrice2) {
	FILE *fp;
	int nbMult, x1, x2, y1, y2;
	int i, j, tmp;

	fp = fopen(file,"r");

	fscanf(fp,"%d",&nbMult);
	fscanf(fp,"%d",&x1);
	fscanf(fp,"%d",&y1);
	fscanf(fp,"%d",&x2);
	fscanf(fp,"%d",&y2);

	matrice1 = malloc(sizeof(int)*x1);
	matrice2 = malloc(sizeof(int)*x2);

	for (i = 0; i < x1; i++)
		*(matrice1+i) = malloc(sizeof(int)*y1);
	for (i = 0; i < x2; i++)
		*(matrice2+i) = malloc(sizeof(int)*y2);

	for (i = 0; i < x1; i++)
	{
		for (j = 0; j < y1; j++)
		{
			fscanf(fp,"%d",&tmp);
			*(*(matrice1+i)+j) = tmp;
		}
	}

	for (i = 0; i < x2; i++)
	{
		for (j = 0; j < y2; j++)
		{
			fscanf(fp,"%d",&tmp);
			*(*(matrice2+i)+j) = tmp;
		}
	}

	fclose(fp);

	return 0;
}

int compute(int** matrice1, int** matrice2) {
	return 0;
}