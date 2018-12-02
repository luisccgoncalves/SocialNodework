#pragma warning(disable:4996)

#include "socialNodework.h"
#include "utils.h"

int main(int argc, char *argv[]) {

	char filename[BUFF];
	int runs, vertices, nodeQty;
	int adjMat[MAXSIZE][MAXSIZE]={ 0 };
	clock_t time;

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
		//printf("Nome do Ficheiro: ");
		//scanf("%49[^\n]s",&filename);
		strcpy(filename, "brock200_1.clq");
	}
	else {
		printf("USAGE: CMD runs filename\n");
		return 0;
	}

	seed_rand();

	time = clock();
	file2adjMat(&adjMat, &vertices, &nodeQty, filename);

	time = clock() - time;

	double time_taken = ((double)time) / CLOCKS_PER_SEC;

	

	printf("took %f seconds to execute \n", time_taken);

	//for (int i = 0; i < nodeQty; i++) {
	//	for (int j = 0; j < nodeQty; j++)
	//		printf("%d ",adjMat[i][j]);
	//	printf("\n");
	//}


	return 0;
}