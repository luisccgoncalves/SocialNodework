#pragma warning(disable:4996)
#include "utils.h"

int* init_dados(char *nome, int *n, int *iter)
{
	FILE    *f;
	int     *p, *q;
	int     i, j;

	f = fopen(nome, "r");
	if (!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
	// Lê o número de iteracoes
	fscanf(f, " %d", iter);
	// Lê o número de vértices
	fscanf(f, " %d", n);
	// Aloca espaço em memória para guardar a matriz de adjacências
	p = malloc(sizeof(int)*(*n)*(*n));
	if (!p)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	q = p;
	// Preenchimento da matriz de adjacências
	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++)
			fscanf(f, " %d", q++);
	fclose(f);
	// Devolve a matriz de adjacências
	return p;
}

void file2adjMat(int adjMat[7][7], int *vertices, char *filename) {

	FILE *f;
	char line[100];
	char type[2];
	int x, y;
	
	f = fopen(filename, "r");
	if (!f) {
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			printf("%d ", adjMat[i][j]);
		}
		printf("\n");
	}

	while (fgets(line,sizeof line,f) != NULL) {
		if (line[0] == 'e') {
			sscanf(line, "%s %d %d", type, &x, &y);
			adjMat[x-1][y-1] = 1;
			adjMat[y - 1][x - 1] = 1;

		}
	}
	printf("\n");
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			printf("%d ", adjMat[i][j]);
		}
		printf("\n");
	}

	fclose(f);
}

void seed_rand() {
	srand((unsigned int)time(NULL));
}

// Gera um valor inteiro aleatório entre min e max
// Parâmetros de entrada: Valor inferior do intervalo, min, Valor superior do intervalo, max
// Parâmetros de saída: Valor aleatório entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

// Gera um valor inteiro aleatório entre 0 e 1
// Parâmetros de saída: Valor aleatório entre 0 e 1
float rand_01()
{
	return ((float)rand()) / RAND_MAX;
}