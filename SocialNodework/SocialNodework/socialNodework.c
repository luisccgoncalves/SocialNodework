#pragma warning(disable:4996)

#include "socialNodework.h"

int main(int argc, char *argv[]) {

	char filename[BUFF];
	int runs;

	if (argc == 3) {
		runs = atoi(argv[2]);

		if (runs<1)
			return 0;
		strcpy(filename, argv[1]);
	}
	else if (argc == 2) {
		runs = DEFAULT_RUNS;
		strcpy(filename, argv[1]);
	}
	else if (argc == 1) {
		runs = DEFAULT_RUNS;
		printf("Nome do Ficheiro: ");
		scanf("%49[^\n]s",&filename);
	}
	else {
		printf("USAGE: CMD runs filename\n");
		return 0;
	}

	printf("\n%s", filename);
	//seed_rand();

	return 0;
}