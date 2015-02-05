#include "generate.h"

int generateFile(int nbMult) {
	FILE* fp;
	int x, y, z;
	int i;

	x = 0;
	y = 0;
	z = 0;

	srand(time(NULL));

	remove("matrice.txt");
	fp = fopen("matrice.txt","a");

	fprintf(fp, "%d\n", nbMult);

	for (i = 0; i < nbMult; i++)
	{
		while(x <= 0)
			x = (rand()%20);
		while(y <= 0)
			y = (rand()%20);
		while(z <= 0)
			z = (rand()%20);

		fprintf(fp, "%d %d\n", x, y);
		fprintf(fp, "%d %d\n", y, z);

		generateMatrice(fp, x, y);
		generateMatrice(fp, y, z);
	}
	fclose(fp);
	return 0;
}

void generateMatrice(FILE* fp, int x, int y) {
	int i, j;
	double tmp;

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			tmp = 10.0*(0.5-((double)rand())/((double)RAND_MAX));
			fprintf(fp, "%.1f ", tmp);
		}
		fprintf(fp, "\n");
	}
}