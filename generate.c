/**
* \file generate.c
* \author Nicolas Le Gall
* \date 09/02/2015
* \brief Permet la génération d'un fichier contenant les matrices
*/

#include "generate.h"

/**
Génère le fichier contenant les matrices
* \param nbMult Nombre de multiplication à faire
* \return Code de retour
*/
int generateFile(int nbMult) {
	FILE* file;
	int x, y, z;
	int i;

	x = 0;
	y = 0;
	z = 0;

	/* Permet une génération 'plus' aléatoire */
	srand(time(NULL));

	/* Supprime le fichier si il existe avant de le créer */
	remove("matrice.txt");
	file = fopen("matrice.txt","a");
	if (file == NULL)
	{
		perror("open file");
		return(EXIT_FAILURE);
	}

	/* Inscription du nombre de multiplication à faire */
	fprintf(file, "%d\n", nbMult);

	for (i = 0; i < nbMult; i++)
	{
		/* Génération des tailles pour les matrices */
		while(x <= 0)
			x = (rand()%20);
		while(y <= 0)
			y = (rand()%20);
		while(z <= 0)
			z = (rand()%20);

		/* Inscription des tailles dans le fichier */
		fprintf(file, "%d %d\n", x, y);
		fprintf(file, "%d %d\n", y, z);
		/* Remplissage des données */
		generateMatrice(file, x, y);
		generateMatrice(file, y, z);
	}
	/* Fermeture du fichier */
	fclose(file);
	return 0;
}

/**
Rempli les lignes et colonnes de la matrice
* \param file Adresse de la pile
* \param x Nombre de ligne
* \param y Nombre de colonnes
*/
void generateMatrice(FILE* file, int x, int y) {
	int i, j;
	double tmp;

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			tmp = 10.0*(0.5-((double)rand())/((double)RAND_MAX));
			fprintf(file, "%.1f ", tmp);
		}
		fprintf(file, "\n");
	}
}