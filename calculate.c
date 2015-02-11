#include "calculate.h"

char* loadFile(const char* file) {
	int fd;
	char* adrMap;
	struct stat st;
	size_t size;

	fd = open(file, O_RDONLY);
	if(fd == -1)
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
	adrMap = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
	if (*adrMap == -1)
	{
		perror("mmap");
		exit(-1);
	}

	close(fd);

	return adrMap;
}

int compute(char* adrMap) {
	int offset, nbCouple;
	float** matrice1;

	int c, i, j, k;

	sscanf(adrMap, "%d%n", &nbCouple, &offset);


	for (c = 0; c < (nbCouple); c++)
	{
		int dimMatrice[4];
		int offset_m1;
		int offset_m2;
		int pastLines;

		getSize(dimMatrice, adrMap, &offset);
		offset_m1 = offset;

		matrice1 = initMatrice(&matrice1, dimMatrice[0], dimMatrice[1]);

		pastLines = offset;
		nextNbLines(adrMap, &pastLines, dimMatrice[0]);
		printf("Taille m1 : %d - %d\n", dimMatrice[0], dimMatrice[1]);
		printf("Taille m2 : %d - %d\n", dimMatrice[2], dimMatrice[3]);
		offset_m2 = pastLines;

		for (i = 0; i < dimMatrice[0]; i++)
		{
			offset_m1 = offset;
			for (j = 0; j < dimMatrice[1]; j++)
			{
				offset_m2 = pastLines;
				offset_m2 += getRelativeOffset(adrMap, offset_m2, i);
				for (k = 0; k < dimMatrice[1]; k++)
				{
					printf("Value : %.1f --- %.1f\n", getValue(adrMap, &offset_m1), getValue(adrMap, &offset_m2));
					printf("Coefficient : %.2f\n", getValue(adrMap, &offset_m1) * getValue(adrMap, &offset_m2));

					nextValue(adrMap, &offset_m1);

					nextNbLines(adrMap, &offset_m2, 0);
					offset_m2 += getRelativeOffset(adrMap ,offset_m2, i);
				}		
			}
		}
	}

	return 0;

}

void getSize(int* dimMatrice, char* data, int* offset) {
	int decalage;
	decalage = 0;

	sscanf((data + *offset),"%d %d%n", &dimMatrice[0], &dimMatrice[1], &decalage );
	*offset += decalage;

	sscanf((data + *offset),"%d %d%n", &dimMatrice[2], &dimMatrice[3], &decalage );
	*offset += decalage;
}

float** initMatrice(float*** matrice, int x, int y) {
	int i;
	*matrice = (float**)malloc(sizeof(float)*x);
	for (i = 0; i < x; i++)
	{
		*(*(matrice)+i) = (float*)malloc(sizeof(float)*y);

	}
	return *matrice;
}

void freeMatrice(float** matrice, int x) {
	int i;
	for (i = 0; i < x; i++)
	{
		free(matrice[i]);
	}
	free(matrice);
}

/*=============================================*/
float getValue(char* file, int* offset) {
	float data;

	sscanf((file + *offset), "%f", &data);

	return data;
}

void nextValue(char* file, int* offset) {
	int decalage;
	float data;

	decalage = 0;

	sscanf((file + *offset), "%f%n", &data, &decalage);
	*offset += decalage;
}

void pastLine(char* file, int* offset, int x) {
	int i, j;
	char* tmp;

	tmp = file + *offset;
	j = 0;

	for (i = 0; i < x; i++)
	{
		while(tmp[j] != '\n') {
			j++;
		}
		*offset += j;
		tmp++;
	}
}

void nextNbLines(char * fmap, int * offset, int nblines)
{
	int i;
	for (i = 0; i <= nblines; i++)
	{
		char * cr;
  		cr = strchr(fmap + *offset,'\n');
  		*offset += (cr-(fmap + *offset)+1);
	}
}

int getRelativeOffset(char * fmap, int offset, int n)
{
	int sv_offset = offset;

	int shift = 0;
	float data;
	int i;

	for (i = 0; i < n; i++)
	{
		sscanf( (fmap + offset), "%f%n", &data, &shift );
		offset += shift;
	}

	return  offset - sv_offset;
}