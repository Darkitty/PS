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
	printf("taille du fichier : %d octets\n",size);
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
	char intChar[3], intChar2[3];
	int nbMult,i;

	tmp = adrMap+2;
	i = 0;

	nbMult = atoi(adrMap);
	printf("nbMult : %d\n", nbMult);

	while(*tmp != ' ')
	{
		intChar[i] = *tmp;
		i++;
		tmp++;
	}

	tmp++;
	i = 0;
	while(*tmp != ' ')
	{
		intChar2[i] = *tmp;
		i++;
		tmp++;
	}

	printf("taille matrice 1 : %d - %d\n", atoi(intChar), atoi(intChar2));
	return 0;
}