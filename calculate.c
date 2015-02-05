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

	tmp = adrMap+2;

	nbMult = atoi(adrMap);
	printf("nbMult : %d\n", nbMult);

	nbMatrice = (int*)malloc(sizeof(int)*nbMult*2);
	printf("nbMatrice (addr mem) : %p\n", (void*)nbMatrice);

	tmp = getSize(nbMatrice, tmp);

	printf("taille matrice 1 : %d - %d\n", nbMatrice[0], nbMatrice[1]);
	return 0;
}

char* getSize(int* nbMatrice, char* data) {
	int i, j;
	char intChar[3];

	j = 0;

	for (i = 0; i < 2; i++)
	{
		while(*data != ' ')
		{
			intChar[j] = *data;
			j++;
			data++;
		}
		nbMatrice[i] = atoi(intChar);

		data++;
		j = 0;
	}

	return data;
}