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
	// L� o n�mero de iteracoes
	fscanf(f, " %d", iter);
	// L� o n�mero de v�rtices
	fscanf(f, " %d", n);
	// Aloca espa�o em mem�ria para guardar a matriz de adjac�ncias
	p = malloc(sizeof(int)*(*n)*(*n));
	if (!p)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	q = p;
	// Preenchimento da matriz de adjac�ncias
	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++)
			fscanf(f, " %d", q++);
	fclose(f);
	// Devolve a matriz de adjac�ncias
	return p;
}

int* file2adjMat(int *vertices, int *arestas, char *filename) {


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

	for (int i = 0; i < *vertices; i++) {
		for (int j = 0; j < *vertices; j++) {
			printf("%d, ",*(adjMat + (*vertices)*i+j));
		}
		printf("\n");
	}

	while (fgets(line,sizeof line,f) != NULL) {

		if (line[0] == 'e') {
			sscanf(line, "%*s %d %d", &x, &y);
			*(adjMat + (*vertices)*(y - 1) + (x - 1)) = 1;
			*(adjMat + (*vertices)*(x - 1) + (y - 1)) = 1;
		}
	}

	for (int i = 0; i < *vertices; i++) {
		for (int j = 0; j < *vertices; j++) {
			printf("%d, ", *(adjMat + (*vertices)*i+j));
		}
		printf("\n");
	}

	fclose(f);

	return adjMat;
}

void adjMat2file(const int *adjMat, int vertices, int arestas, const char *filename) {

	FILE *f;

	f = fopen(filename, "w");

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			fprintf(f, "%d, ", *(adjMat + (vertices)*i + j));
			printf("%d, ", *(adjMat + (vertices)*i + j));
		}
		fprintf(f, "\n");
		printf("\n");
	}

	fclose(f);
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

// Gera um valor inteiro aleat�rio entre 0 e 1
// Par�metros de sa�da: Valor aleat�rio entre 0 e 1
float rand_01()
{
	return ((float)rand()) / RAND_MAX;
}