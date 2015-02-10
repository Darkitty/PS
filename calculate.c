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
	char* tmp;
	int nbMult;
	int* nbMatrice;
	int offset, offset_2;
	float** matrice1;
	int i;

	tmp = adrMap+2;
	offset = 0;

	nbMult = atoi(adrMap);
	printf("nbMult : %d\n", nbMult);

	nbMatrice = (int*)malloc(sizeof(int)*nbMult*2);
	printf("nbMatrice (addr mem) : %p\n", (void*)nbMatrice);

	getSize(nbMatrice, tmp, &offset);

	printf("taille matrice 1 : %d - %d\n", nbMatrice[0], nbMatrice[1]);
	printf("taille matrice 2 : %d - %d\n", nbMatrice[2], nbMatrice[3]);

	matrice1 = initMatrice(&matrice1, nbMatrice[0], nbMatrice[1]);

	printf("Matrice 1 : %p\n", (void*)matrice1);

	offset += 2;
	for (i = 0; i < nbMatrice[1]; i++)
	{
		printf("Offset : %d - Value %.1f\n", offset, getValue(adrMap, &offset));
	}

	offset_2 = offset;
	printf("-------------------------\n");
	pastLine(adrMap, &offset_2, nbMatrice[0]);
	nextColumn(adrMap, &offset_2, 6);
	for (i = 0; i < nbMatrice[2]; i++)
	{
		nextColumn(adrMap, &offset_2, 3);
		printf("Offset : %d - Value %.1f\n", offset_2, getValue(adrMap, &offset_2));
		pastLine(adrMap, &offset_2, 1);
	}

	freeMatrice(matrice1, nbMatrice[0]);
	free(nbMatrice);

	return 0;
}

char* getSize(int* nbMatrice, char* data, int* offset) {
	int decalage;
	decalage = 0;

	sscanf((data + *offset),"%d %d%n", &nbMatrice[0], &nbMatrice[1], &decalage );
	*offset += decalage;

	sscanf((data + *offset),"%d %d%n", &nbMatrice[2], &nbMatrice[3], &decalage );
	*offset += decalage;
	
	return data;
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
	int decalage;
	float data;

	decalage = 0;

	sscanf((file + *offset), "%f%n", &data, &decalage);
	*offset += decalage;

	return data;
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

void nextColumn(char* file, int* offset, int x) {
	int i, j, cmp;
	char* tmp;

	tmp = file + *offset;

	for (i = 0; i < (x-1); i++)
	{
		while(tmp[j] != ' ') {
			if(tmp[j] == '-')
				cmp++;
			j++;
		}
		*offset = *offset + j;
		j = 0;
		cmp = 0;
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