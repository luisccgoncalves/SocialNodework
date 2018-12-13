#include "algorithms.h"

//void bruteForce(int solution[MAXSIZE], int adjMat[MAXSIZE][MAXSIZE], int vertices, int arestas) {
//
//	int pos = 0;
//	int adjList[MAXSIZE][MAXSIZE] = { 0 };
//	int curSol[MAXSIZE] = { 0 };
//
//	for (int i = 0; i < vertices; i++) {
//		for (int j = 0; j < vertices; j++) {
//			if(adjMat[i][j]==0)
//				adjList[i][pos++] = j+1;
//		}
//
//		//for (int j = 0; j < pos; j++)
//		//	printf("%d, ", curSol[j]);
//		//printf("\n");
//
//		pos = 0;
//
//	}
//	for (int i = 0; i < vertices; i++) {
//		for (int j = 0;adjList[i][j]!=0; j++) {
//			printf("%d, ", adjList[i][j]);
//		}
//		printf("\n");
//	}
//}

// Gera um vizinho à distância 1 (troca um vértice de cada grupo)
// Parâmetros de entrada: Solução actual, a, Solução vizinha, b, Número de vértices, n
void gera_vizinho(int a[], int b[], int n, int viz){

	int i, j;
	// Copia a solução atual para a solução vizinha
	for (i = 0; i < n; i++)
		b[i] = a[i];

	if (viz > n)
		viz = n;

	int *vizMat = malloc((sizeof (int))*viz);
	for (i = 0; i < viz; i++) {

		while (1) {
			vizMat[i] = random_l_h(0, n - 1);
			for (j = 0; j < i; j++)
				if (vizMat[i] == vizMat[j])
					break;
			if (j == i)
				break;
		} 
	}


	for (i = 0; i < viz; i++) {
		b[vizMat[i]] = !b[vizMat[i]];
	}

	free(vizMat);
}

// Trepa colinas first-choice
// Parâmetros de entrada: Solucao, sol, Matriz de adjacencias, mat, Número de vértices, vert, Número de iterações, num_iter
// Parâmetros de saída: Custo da melhor solução encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
	int *nova_sol, custo, custo_viz, i;

	// Aloca espaço em memória para guardar a nova solução
	nova_sol = malloc(sizeof(int)*vert);
	// Caso não consiga fazer a alocação, envia aviso e termina o programa
	if (nova_sol == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	// Avalia solução inicial
	custo = calcula_fit(sol, mat, vert);		//==============================>>>>
	for (i = 0; i < num_iter; i++){
		// Gera solução vizinha
		gera_vizinho(sol, nova_sol, vert, 2);		//==============================>>>>>
		//printSolution(nova_sol, vert);
		custo_viz = calcula_fit(nova_sol, mat, vert);
		if (custo_viz > custo){
			substitui(sol, nova_sol, vert);			//================================>>>>>>>>>>>>>>>>>>>>>>
			custo = custo_viz;
		}
	}
	// Liberta a memória usada para guardar a nova solução

	free(nova_sol);
	// Devolve o custo da melhor solução encontrada
	return custo;
}