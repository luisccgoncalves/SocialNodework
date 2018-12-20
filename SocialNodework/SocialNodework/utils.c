#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "utils.h"


void file2adjMat(int **mainAdjMat, int *vertices, int *arestas, char *filename) {


	FILE *f;
	char line[100];
	int x, y;
	int *adjMat;
	
	f = fopen(filename, "r");
	if (!f) {
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	//Vai lendo linhas e descartando-as, se a linha come�ar por p, grava os vertices e arestas e sai do ciclo
	while (fgets(line, sizeof line, f) != NULL) {

		if (line[0] == 'p') {
			sscanf(line, "%*s %*s %d %d", vertices, arestas);
			break;
		}

	}

	adjMat = malloc(sizeof(int)*(*vertices)*(*vertices));
	if (!adjMat) {
		printf("Erro de memoria!\n");
		exit(1);
	}
	
	for (int i = 0; i < *vertices; i++) {
		for (int j = 0; j < *vertices; j++) {
			*(adjMat + (*vertices)*i+j) = 0;
		}
	}

	while (fgets(line,sizeof line,f) != NULL) {

		if (line[0] == 'e') {
			sscanf(line, "%*s %d %d", &x, &y);
			*(adjMat + (*vertices)*(y - 1) + (x - 1)) = 1;
			*(adjMat + (*vertices)*(x - 1) + (y - 1)) = 1;
		}
	}

	fclose(f);

	*mainAdjMat=adjMat;
}

void adjMat2file(const int *adjMat, int vertices, int arestas, const char *filename) {

	FILE *f;

	f = fopen(filename, "w");
	if (!f) {
		printf("Erro no acesso ao ficheiro\n");
		exit(1);
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			fprintf(f, "%d, ", *(adjMat + (vertices)*i + j));
		}
		fprintf(f, "\n");
	}

	fclose(f);
}

void populateSolution(int *solution, int vertices) {

	for (int i = 0; i < vertices; i++) {
		*(solution + i) = flipCoin();
	}
}

void printSolution(int *solution, int vertices) {

	for (int i = 0; i < vertices; i++)
		if (solution[i])
			printf("%2d  ", i+1);
	printf("\n");
}

void seed_rand() {
	srand((unsigned int)time(NULL));
}

// Gera um valor inteiro aleat�rio entre min e max
// Par�metros de entrada: Valor inferior do intervalo, min, Valor superior do intervalo, max
// Par�metros de sa�da: Valor aleat�rio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

// Gera um valor decimal aleat�rio entre 0 e 1
// Par�metros de sa�da: Valor aleat�rio entre 0 e 1
float rand_01(){
	return ((float)rand()) / RAND_MAX;
}

//Gera 0 ou 1 com 50% de probabilidade
int flipCoin() {
	return rand() % 2;
}

// Calcula a qualidade de uma solu��o
// Par�metros de entrada: Solu��o actual, a, Matriz de adjac�ncias, mat, N�mero de v�rtices, vert
// Par�metros de sa�da: Custo, total - Neste caso, � o n�mero de liga��es que existem entre os v�rtices do grupo
int calcula_fit(int a[], int *mat, int vert)
{
	int colisao = 0, total=0;
	int i, j;

	for (i = 0; i < vert; i++) {
		if (a[i]) {
			total++;					//Conta 1 n� na solu��o
			for (j = 0; j < vert; j++)
				if (a[j] && *(mat + i * vert + j))
					colisao++;			//Se o n� tiver uma colis�o com outro membro da solu��o, conta uma colis�o
		}
	}

	if (colisao == 0)
		return total;		//Se n�o houverem colis�es, � uma solu��o v�lida e devolve o n� de n�s do grupo
	else
		return -colisao;	//Se houverem penaliza a qualidade. (MAIS colis�es == MENOS qualidade)
}

void createCSV(	int		runs, 
				int		maxIterations, 
				int		vertices, 
				float	mbf, 
				int		bestCusto, 
				double	timeTaken, 
				int		*solutionStorage,
				int		*custoStorage,
				const char *filename, 
				const char *outputDir
	) {

	char newFilename[100];
	strcpy(newFilename, outputDir);
	strcat(newFilename, filename);


	FILE * fCSV = fopen(strcat(strtok(newFilename,"."),".csv"), "w");	//cria um CSV com o nome do clq ou txt
	if (!fCSV) {
		printf("Erro no acesso ao ficheiro CSV\n");
		exit(1);
	}

	time_t rawtime;
	struct tm *info;
	time(&rawtime);
	info = localtime(&rawtime);

	fprintf(fCSV, "DATA:;%s\n", asctime(info));
	fprintf(fCSV, "Ficheiro:;%s\n", filename);
	fprintf(fCSV, "Tembo decorrido:;%.3f\n", timeTaken);
	fprintf(fCSV, "Runs:; %d\n", runs);
	fprintf(fCSV, "Iteracoes:;%d\n", maxIterations);
	fprintf(fCSV, "MBF:; %.3f\n", mbf);
	fprintf(fCSV, "Melhor solucao:; %d\n", bestCusto);

	for (int i = 0; i < runs; i++) {
		fprintf(fCSV, "%d;", *(custoStorage + i));
	}
	fprintf(fCSV, "\n");

	for (int i = 0; i < runs; i++) {
		for (int j = 0; j < vertices; j++) {
			if (*(solutionStorage + i * vertices + j))
				fprintf(fCSV, "%d;", j + 1);
		}
		fprintf(fCSV, "\n");
	}

	fclose(fCSV);
}