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

	int c, i, j, k;

	sscanf(adrMap, "%d%n", &nbCouple, &offset);

	remove("resultat.txt");

	for (c = 0; c < (nbCouple); c++)
	{
		int dimMatrice[4];
		int offset_m1;
		int offset_m2;
		int pastLines;
		float value;
		float** resultat;
		FILE* file;

		/* Thread attributes */
		/*int cpuNumber;
		pthread_t* threads;
		pthread_attr_t attr;
		cpu_set_t cpus;*/
		/* ----------------- */

		/* ----------------- */
		/*cpuNumber = sysconf(_SC_NPROCESSORS_ONLN);
		threads = (pthread_t*)malloc(sizeof(pthread_t));
		pthread_attr_init(&attr);*/
		/* ----------------- */

		file = fopen("resultat.txt","a");
		if (file == NULL)
		{
			perror("open file");
			return(EXIT_FAILURE);
		}

		getSize(dimMatrice, adrMap, &offset);
		offset_m1 = offset;

		resultat = initMatrice(&resultat, dimMatrice[0], dimMatrice[3]);

		printf("Taille m1 : %d - %d\n", dimMatrice[0], dimMatrice[1]);
		printf("Taille m2 : %d - %d\n", dimMatrice[2], dimMatrice[3]);

		fprintf(file, "%d %d\n", dimMatrice[0], dimMatrice[3]);

		pastLines = offset;
		pastLine(adrMap, &pastLines, dimMatrice[0]);
		offset_m2 = pastLines;

		pastLine(adrMap, &offset, dimMatrice[0] + dimMatrice[2]);

		for (i = 0; i < dimMatrice[1]; i++)
		{
			offset_m1 = offset;
			for (j = 0; j < dimMatrice[0]; j++)
			{
				value = 0.0;
				offset_m2 = pastLines;
				offset_m2 += getRelativeOffset(adrMap, offset_m2, i);
				for (k = 0; k < dimMatrice[1]; k++)
				{
					value += getValue(adrMap, &offset_m1) * getValue(adrMap, &offset_m2);

					nextValue(adrMap, &offset_m1);

					pastLine(adrMap, &offset_m2, 0);
					offset_m2 += getRelativeOffset(adrMap ,offset_m2, i);
				}
				fprintf(file, "%.2f ", value);		
			}
			fprintf(file, "\n");
		}
		printf("-----------------------\n");
		fprintf(file, "---------------------\n");
	fclose(file);
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

void pastLine(char * file, int * offset, int x)
{
	int i;
	for (i = 0; i <= x; i++)
	{
		char * cr;
  		cr = strchr(file + *offset,'\n');
  		*offset += (cr-(file + *offset)+1);
	}
}

int getRelativeOffset(char * file, int offset, int n)
{
	int tmp = offset;

	int decalage = 0;
	float null;
	int i;

	for (i = 0; i < n; i++)
	{
		sscanf((file + offset), "%f%n", &null, &decalage );
		offset += decalage;
	}

	return  (offset - tmp);
}