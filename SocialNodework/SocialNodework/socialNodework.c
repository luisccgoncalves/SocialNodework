#pragma warning(disable:4996)

#include "socialNodework.h"
#include "utils.h"
#include "algorithms.h"

int main(int argc, char *argv[]) {

	char filename[BUFF];
	int runs, vertices, arestas, custo;
	int *adjMat=NULL;
	int *solution, *bestSolution;
	float mbf=0;
	clock_t time;
	//time = clock();
	//time = clock() - time;
	//double time_taken = ((double)time) / CLOCKS_PER_SEC;
	//printf("took %f seconds to execute \n", time_taken);

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
		strcpy(filename, "c-fat500-1.clq");
	}
	else {
		printf("USAGE: CMD runs filename\n");
		return 0;
	}

	seed_rand();

	file2adjMat(&adjMat, &vertices, &arestas, filename);

	solution = malloc(sizeof(int)*vertices);
	bestSolution = malloc(sizeof(int)*vertices);
	if (!solution || !bestSolution) {
		printf("Erro de memoria!\n");
		exit(1);
	}

	for (int i = 0; i < runs; i++) {

		populateSolution(solution, vertices);
		//printSolution(solution, vertices);

		custo = trepa_colinas(solution, adjMat, vertices, MAX_ITERATIONS);


		printf("Repeticao %d:", i);
		printSolution(solution, vertices);
		printf("Qualidade: %2d\n\n", custo);

		mbf += custo;
	}

	printf("\nMBF: %f", mbf / runs);

	//bruteForce(solution, adjMat, vertices, arestas);
	adjMat2file(adjMat, vertices, arestas, "mat2.txt");

	free(adjMat);
	free(solution);
	free(bestSolution);

	return 0;
}