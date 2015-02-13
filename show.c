#include "show.h"

int show() {
	FILE* file;
	char line[80];

	file = fopen("resultat.txt","r");
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