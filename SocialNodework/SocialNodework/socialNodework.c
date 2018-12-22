#pragma warning(disable:4996)

#include "socialNodework.h"
#include "utils.h"
#include "algorithms.h"

int main(int argc, char *argv[]) {

	char filename[BUFF];
	char fileAddr[BUFF] = DATA_DIR;
	int runs, vertices, arestas, custo, bestCusto;
	int *adjMat=NULL;
	int *solution, *bestSolution;
	int *solutionStorage, *custoStorage;
	float mbf=0;
	clock_t time;

	if (argc == 3) {
		runs = atoi(argv[2]);

		if (runs<1)
			return 0;
		strcat(fileAddr, argv[1]);
	}
	else if (argc == 2) {
		runs = DEFAULT_RUNS;
		strcat(fileAddr, argv[1]);
	}
	else if (argc == 1) {
		runs = DEFAULT_RUNS;
		//printf("Nome do Ficheiro: ");
		//scanf("%49[^\n]s",&filename);
		strcpy(filename, "johnson8-2-4.clq");
		strcat(fileAddr, filename);
	}
	else {
		printf("USAGE: CMD runs filename\n");
		return 0;
	}

	time = clock(); //Começa a contar o tempo a partir daqui

	seed_rand();

	file2adjMat(&adjMat, &vertices, &arestas, fileAddr);

	solution = malloc(sizeof(int)*vertices);
	bestSolution = malloc(sizeof(int)*vertices);

	//Variáveis usadas apenas no CSV
	solutionStorage = malloc(sizeof(int)*vertices*runs);
	custoStorage = malloc(sizeof(int)*runs);

	//Verificação de erro de alocação de memória
	if (!solution || !bestSolution || !solutionStorage || !custoStorage) {
		printf("Erro de memoria!\n");
		exit(1);
	}

	for (int i = 0; i < runs; i++) {

		populateSolution(solution, vertices);

		custo = trepa_colinas(solution, adjMat, vertices, MAX_ITERATIONS);

		printf("Repeticao %d:\n", i+1);
		printSolution(solution, vertices);
		printf("Qualidade: %2d\n\n", custo);

		memcpy(solutionStorage + vertices*i, solution, sizeof(int)*vertices);
		*(custoStorage + i) = custo;

		mbf += custo;

		if (i == 0 || bestCusto < custo) {
			bestCusto = custo;
			memcpy(bestSolution, solution, sizeof(int)*vertices);
		}
	}

	mbf = mbf / runs;

	double timeTaken = ((double)(clock() - time)) / CLOCKS_PER_SEC; //Para de contar o tempo aqui

	printf("\nMBF: %.3f", mbf);
	printf("\nMelhor solucao: ");
	printSolution(bestSolution, vertices);
	printf("Qualidade: %d\n", bestCusto);
	printf("Tempo de execucao: %.3f seg\n", timeTaken);

	createCSV(	runs, 
				MAX_ITERATIONS, 
				vertices,
				mbf, 
				bestCusto, 
				timeTaken, 
				solutionStorage,
				custoStorage,
				filename, 
				OUTPUT_DIR);

	adjMat2file(adjMat, vertices, arestas, "mat2.txt");

	free(adjMat);
	free(solution);
	free(bestSolution);
	free(custoStorage);
	free(solutionStorage);

	return 0;
}