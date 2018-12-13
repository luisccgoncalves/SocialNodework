#pragma warning(disable:4996)
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

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			fprintf(f, "%d, ", *(adjMat + (vertices)*i + j));
			//printf("%d, ", *(adjMat + (vertices)*i + j));
		}
		fprintf(f, "\n");
		//printf("\n");
	}

	fclose(f);
}

void populateSolution(int *solution, int vertices) {

	for (int i = 0; i < vertices; i++) {
		*(solution + i) = flipCoin();
	}
}

void printSolution(int *solution, int vertices) {

	int i;

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

// Gera um valor inteiro aleat�rio entre 0 e 1
// Par�metros de sa�da: Valor aleat�rio entre 0 e 1
float rand_01()
{
	return ((float)rand()) / RAND_MAX;
}

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
			total++;
			for (j = 0; j < vert; j++)
				if (a[j] && *(mat + i * vert + j))
					colisao++;
		}
	}

	if (colisao == 0)
		return total;
	else
		return -colisao;
}

// copia vector b para a (tamanho n)
// Par�metros de entrada: Solu��o que ser� substitu�da, a, Solu��o que ir� substituir, b, N�mero de vertices, n
void substitui(int a[], int b[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		a[i] = b[i];
}