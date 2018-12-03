#pragma warning(disable:4996)

#include "socialNodework.h"
#include "utils.h"
#include "algorithms.h"

int main(int argc, char *argv[]) {

	char filename[BUFF];
	int runs, vertices, arestas;
	int adjMat[MAXSIZE][MAXSIZE]={ 0 };
	int solution[MAXSIZE] = { 0 };
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
		strcpy(filename, "inst_teste.txt");
	}
	else {
		printf("USAGE: CMD runs filename\n");
		return 0;
	}

	seed_rand();

	time = clock();
	file2adjMat(&adjMat, &vertices, &arestas, filename);

	//time = clock() - time;
	//double time_taken = ((double)time) / CLOCKS_PER_SEC;
	//printf("took %f seconds to execute \n", time_taken);

	bruteForce(&solution, &adjMat, vertices, arestas);
	//adjMat2file(adjMat, vertices, arestas, "mat2.txt");

	return 0;
}