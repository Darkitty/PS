#include "generate.h"

int generateFile(int nbMult, int x1, int y1, int x2, int y2) {
	FILE* fp;

	x1 =10.0*(0.5-((double)rand())/((double)RAND_MAX));
	y1 =10.0*(0.5-((double)rand())/((double)RAND_MAX));
	x2 =10.0*(0.5-((double)rand())/((double)RAND_MAX));
	y2 =10.0*(0.5-((double)rand())/((double)RAND_MAX));

	remove("matrice.txt");
	fp = fopen("matrice.txt","a");

	fprintf(fp, "%d\n", nbMult);
	

	fclose(fp);
	return 0;
}

int checkSize(int y1, int x2) {
	if (y1 != x2)
		return -1;
	return 0;
}