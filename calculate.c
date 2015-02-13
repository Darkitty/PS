/**
* \file generate.c
* \author Nicolas Le Gall
* \date 09/02/2015
* \brief Permet le calcul et la gestion des matrices
*/
#include "calculate.h"

/* Permet de mapper le fichier dans la memoire */
char* loadFile(const char* file_name) {
	int file;
	char* adrMap;
	struct stat st;
	size_t size;

	file = open(file_name, O_RDONLY);
	if(file == -1)
	{
		perror("open");
		exit(-1);
	}
	if(stat("matrice.txt", &st))
	{
		perror("stat");
		exit(-1);
	}

	size = st.st_size;
	printf("taille du fichier : %d octets\n",(int)size);

	adrMap = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, file, 0);

	if (*adrMap == -1)
	{
		perror("mmap");
		exit(-1);
	}

	close(file);

	return adrMap;
}

/*
Effectue le produit matriciel pour l'ensemble des matrices
presente dans le fichier
*/
int compute(char* adrMap) {
	int offset, nbCouple;

	/* Variables pour les boucles */
	int c, i, j, k;

	sscanf(adrMap, "%d%n", &nbCouple, &offset);

	/* On supprime l'ancien fichier resultat */
	remove("resultat.txt");

	for (c = 0; c < (nbCouple); c++)
	{
		FILE* file;
		int dimMatrice[4];
		int offset_m1;
		int offset_m2;
		int pastLines;
		float value;

		file = fopen("resultat.txt","a");
		if (file == NULL)
		{
			perror("open file");
			return(EXIT_FAILURE);
		}

		/* On recupere les tailles des matrices */
		getSize(dimMatrice, adrMap, &offset);
		/* On defini l'offset_m1 sur le debut de la matrice 1 */
		offset_m1 = offset;

		printf("Taille m1 : %d - %d\n", dimMatrice[0], dimMatrice[1]);
		printf("Taille m2 : %d - %d\n", dimMatrice[2], dimMatrice[3]);

		/* On ecrit la taille de la matrice resultante */
		fprintf(file, "%d %d\n", dimMatrice[0], dimMatrice[3]);

		/* On d¨¦place offset_m2 au debut de la deuxieme matrice */
		pastLines = offset;
		pastLine(adrMap, &pastLines, dimMatrice[0]);
		offset_m2 = pastLines;

		pastLine(adrMap, &offset, dimMatrice[0] + dimMatrice[2]);

		/* Pour chaque colonne */
		for (i = 0; i < dimMatrice[1]; i++)
		{
			offset_m1 = offset;
			/* Pour chaque ligne */
			for (j = 0; j < dimMatrice[0]; j++)
			{
				value = 0.0;
				offset_m2 = pastLines;
				/* On deplace offset_m2 sur la valeur suivante */
				offset_m2 += getRelativeOffset(adrMap, offset_m2, i);
				/* Pour chaque colonne */
				for (k = 0; k < dimMatrice[1]; k++)
				{
					/* On mutliplie la colonne et la ligne */
					value += getValue(adrMap, &offset_m1) * getValue(adrMap, &offset_m2);
					/* On deplace offset_m1 d'une colonne */
					nextValue(adrMap, &offset_m1);

					/* On deplace offset_m2 d'une ligne */
					pastLine(adrMap, &offset_m2, 0);
					offset_m2 += getRelativeOffset(adrMap ,offset_m2, i);
				}
				/* On ecrit le resultat dans le fichier */
				fprintf(file, "%.2f ", value);		
			}
			/* Ligne suivante */
			fprintf(file, "\n");
		}
		printf("-----------------------\n");
		fprintf(file, "---------------------\n");
		fclose(file);
	}
	/* On supprime le mmap dans la m¨¦moire */
	munmap(adrMap, getFileSize("matrice.txt"));
	return 0;
}

/*=============================================*/

/* Recupere la taille des deux matrices a calculer */
void getSize(int* dimMatrice, char* data, int* offset) {
	int decalage;
	decalage = 0;

	sscanf((data + *offset),"%d %d%n", &dimMatrice[0], &dimMatrice[1], &decalage );
	*offset += decalage;

	sscanf((data + *offset),"%d %d%n", &dimMatrice[2], &dimMatrice[3], &decalage );
	*offset += decalage;
}

/* Recuperer la valeur dans le mmap a l'offset */
float getValue(char* file, int* offset) {
	float data;

	sscanf((file + *offset), "%f", &data);

	return data;
}

/* Deplace l'offset d'une valeur dans le mmap */
void nextValue(char* file, int* offset) {
	int decalage;
	float null;

	decalage = 0;

	sscanf((file + *offset), "%f%n", &null, &decalage);
	*offset += decalage;
}

/* Passe x ligne dans le mmap */
void pastLine(char * file, int * offset, int x) {
	int i;
	for (i = 0; i <= x; i++)
	{
		char * cr;
  		cr = strchr(file + *offset,'\n');
  		*offset += (cr-(file + *offset)+1);
	}
}

/* Donne le deplacement pour passer x valeurs */
int getRelativeOffset(char * file, int offset, int x) {
	int tmp = offset;

	int decalage = 0;
	float null;
	int i;

	for (i = 0; i < x; i++)
	{
		sscanf((file + offset), "%f%n", &null, &decalage );
		offset += decalage;
	}
	return  (offset - tmp);
}

/* ------------------------------------------- */

/* Donne la taille dd'un fichier */
int getFileSize(const char* file_name) {
	int file;
	struct stat st;
	size_t size;

	file = open(file_name, O_RDONLY);
	if(file == -1)
	{
		perror("open");
		exit(-1);
	}
	if(stat("matrice.txt", &st))
	{
		perror("stat");
		exit(-1);
	}

	size = st.st_size;
	close(file);
	return size;
}