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

	//Vai lendo linhas e descartando-as, se a linha começar por p, grava os vertices e arestas e sai do ciclo
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

// Gera um valor inteiro aleatório entre min e max
// Parâmetros de entrada: Valor inferior do intervalo, min, Valor superior do intervalo, max
// Parâmetros de saída: Valor aleatório entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

// Gera um valor decimal aleatório entre 0 e 1
// Parâmetros de saída: Valor aleatório entre 0 e 1
float rand_01(){
	return ((float)rand()) / RAND_MAX;
}

//Gera 0 ou 1 com 50% de probabilidade
int flipCoin() {
	return rand() % 2;
}

// Calcula a qualidade de uma solução
// Parâmetros de entrada: Solução actual, a, Matriz de adjacências, mat, Número de vértices, vert
// Parâmetros de saída: Custo, total - Neste caso, é o número de ligações que existem entre os vértices do grupo
int calcula_fit(int a[], int *mat, int vert)
{
	int colisao = 0, total=0;
	int i, j;

	for (i = 0; i < vert; i++) {
		if (a[i]) {
			total++;					//Conta 1 nó na solução
			for (j = 0; j < vert; j++)
				if (a[j] && *(mat + i * vert + j))
					colisao++;			//Se o nó tiver uma colisão com outro membro da solução, conta uma colisão
		}
	}

	if (colisao == 0)
		return total;		//Se não houverem colisões, é uma solução válida e devolve o nº de nós do grupo
	else
		return -colisao;	//Se houverem penaliza a qualidade. (MAIS colisões == MENOS qualidade)
}

void createCSV() {

	FILE * fCSV = fopen("batatas.csv", "w");
	if (!fCSV) {
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	fprintf(fCSV, "EU;GOSTO;DE;BATATAS");

	fclose(fCSV);
}