#include "generate.h"
#include "calculate.h"

int main(int argc, char const *argv[])
{
	int nbMult;
	int** matrice1;
	int** matrice2;

	if (argc < 2)
	{
		printf("usage: %s nbMult\n",argv[0]);
		return(EXIT_FAILURE);
	}

	sscanf(argv[1],"%u",(unsigned int*)&nbMult);
	
	if (generateFile(nbMult) != 0)
	{
		printf("Erreur lors de la generation du fichier");
		return(EXIT_FAILURE);
	}

	printf("==============================\n");
	printf("|Generation du fichier reussi|\n");
	printf("==============================\n");

	printf("==============================\n");
	printf("|   Initialisation matrices  |\n");
	printf("==============================\n");

	intMatrice("matrice.txt", matrice1, matrice2);

	printf("==============================\n");
	printf("|   Calcul des matrices      |\n");
	printf("==============================\n");

	compute(matrice1, matrice2);

	return 0;
}