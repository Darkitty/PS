#include "generate.h"

int generateFile(int nbMult, int x1, int y1, int x2, int y2) {
	FILE* fp;
	int i, j, tmp;

	remove("matrice.txt");
	fp = fopen("matrice.txt","a");

	fprintf(fp, "%d\n", nbMult);
	fprintf(fp, "%d %d\n", x1, y1);
	fprintf(fp, "%d %d\n", x2, y2);

	for (j = 0; j < x1; j++)
	{
		for (i = 0; i < y1; i++)
		{
			tmp = 10.0*(0.5-((double)rand())/((double)RAND_MAX));
			fprintf(fp, "%d ", tmp);
		}
		fprintf(fp, "\n");
	}

	for (j = 0; j < x2; j++)
	{
		for (i = 0; i < y2; i++)
		{
			tmp = 10.0*(0.5-((double)rand())/((double)RAND_MAX));
			fprintf(fp, "%d ", tmp);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
	return 0;
}

int checkSize(int y1, int x2) {
	if (y1 != x2)
		return -1;
	return 0;
}