#include "generate.h"
#include "calculate.h"

int main(int argc, char const *argv[])
{
	int x1, y1, x2, y2;
	if (argc < 5)
	{
		printf("usage: %s nbMult matrice_x1 matrice_y1 matrice_x2 matrice_y2\n",argv[0]);
		return(EXIT_FAILURE);
	}
	sscanf(argv[2],"%u",(unsigned int*)&x1);
	sscanf(argv[3],"%u",(unsigned int*)&y1);
	sscanf(argv[4],"%u",(unsigned int*)&x2);
	sscanf(argv[5],"%u",(unsigned int*)&y2);
	if (checkSize(x2, y1) == -1)
	{
		printf("Le nombre de ligne de la matrice 1 doit etre egale au nombre de collone de la matrice 2");
		return(EXIT_FAILURE);
	}
	return 0;
}