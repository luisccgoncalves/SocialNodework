#include "algorithms.h"

void gera_vizinho(int a[], int b[], int n, int viz){

	int i, j;
	int running = 1;

	// Copia a solução atual para a solução vizinha
	memcpy(b, a, sizeof(int)*n);

	//Não podem haver mais vizinhos que vértices 
	if (viz > n)
		viz = n;

	int *vizMat = malloc((sizeof (int))*viz);

	for (i = 0; i < viz; i++) {
		while (running) {
			vizMat[i] = random_l_h(0, n - 1);	//Selecciona um vértice aleatório
			for (j = 0; j < i; j++)
				if (vizMat[i] == vizMat[j])		//Verifica se já foi seleccionado anteriormente
					break;
			if (j == i)
				break;
		} 
	}

	//Inverte os valores do respectivos vizinhos
	for (i = 0; i < viz; i++) {
		b[vizMat[i]] = !b[vizMat[i]];
	}

	free(vizMat);
}

int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
	int *nova_sol, custo, custo_viz, i;

	// Aloca espaço em memória para guardar a nova solução
	nova_sol = malloc(sizeof(int)*vert);
	if (nova_sol == NULL){
		printf("Erro na alocacao de memoria");
		exit(1);
	}

	// Avalia solução inicial
	custo = calcula_fit(sol, mat, vert);

	for (i = 0; i < num_iter; i++){
		// Gera solução vizinha
		gera_vizinho(sol, nova_sol, vert, 1);

		//Se a solução vizinha for melhor, passa a ser essa a solução
		custo_viz = calcula_fit(nova_sol, mat, vert);
		if (custo_viz > custo){
			memcpy(sol, nova_sol, sizeof (int)*vert);
			custo = custo_viz;
		}
	}

	// Liberta a memória usada para guardar a nova solução
	free(nova_sol);
	// Devolve o custo da melhor solução encontrada
	return custo;
}