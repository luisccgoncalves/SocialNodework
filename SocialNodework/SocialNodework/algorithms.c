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

// Gera um vizinho � dist�ncia 1 (troca um v�rtice de cada grupo)
// Par�metros de entrada: Solu��o actual, a, Solu��o vizinha, b, N�mero de v�rtices, n
void gera_vizinho(int a[], int b[], int n, int viz){

	int i, j;
	// Copia a solu��o atual para a solu��o vizinha
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
// Par�metros de entrada: Solucao, sol, Matriz de adjacencias, mat, N�mero de v�rtices, vert, N�mero de itera��es, num_iter
// Par�metros de sa�da: Custo da melhor solu��o encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
	int *nova_sol, custo, custo_viz, i;

	// Aloca espa�o em mem�ria para guardar a nova solu��o
	nova_sol = malloc(sizeof(int)*vert);
	// Caso n�o consiga fazer a aloca��o, envia aviso e termina o programa
	if (nova_sol == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	// Avalia solu��o inicial
	custo = calcula_fit(sol, mat, vert);		//==============================>>>>
	for (i = 0; i < num_iter; i++){
		// Gera solu��o vizinha
		gera_vizinho(sol, nova_sol, vert, 2);		//==============================>>>>>
		//printSolution(nova_sol, vert);
		custo_viz = calcula_fit(nova_sol, mat, vert);
		if (custo_viz > custo){
			substitui(sol, nova_sol, vert);			//================================>>>>>>>>>>>>>>>>>>>>>>
			custo = custo_viz;
		}
	}
	// Liberta a mem�ria usada para guardar a nova solu��o

	free(nova_sol);
	// Devolve o custo da melhor solu��o encontrada
	return custo;
}