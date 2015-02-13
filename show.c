/**
* \file generate.c
* \author Nicolas Le Gall
* \date 09/02/2015
* \brief Permet l'affichage du fichier contenant les matrices resultantes
*/

#include "define.h"
#include "show.h"

/* Affiche le contenu des matrices resultantes */
int show() {
	FILE* file;
	char line[80];

	file = fopen(FILE_OUT,"r");
	if (file == NULL)
	{
		perror("open file");
		return(EXIT_FAILURE);
	}

	while(fgets(line, 80, file) != NULL)
		printf ("%s\n", line);

	fclose(file);
	return 0;
}