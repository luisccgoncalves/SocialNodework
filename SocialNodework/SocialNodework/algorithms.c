#include "algorithms.h"

void gera_vizinho(int a[], int b[], int n, int viz){

	int i, j;
	int running = 1;

	// Copia a solu��o atual para a solu��o vizinha
	memcpy(b, a, sizeof(int)*n);

	//N�o podem haver mais vizinhos que v�rtices 
	if (viz > n)
		viz = n;

	int *vizMat = malloc((sizeof (int))*viz);

	for (i = 0; i < viz; i++) {
		while (running) {
			vizMat[i] = random_l_h(0, n - 1);	//Selecciona um v�rtice aleat�rio
			for (j = 0; j < i; j++)
				if (vizMat[i] == vizMat[j])		//Verifica se j� foi seleccionado anteriormente
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

	// Aloca espa�o em mem�ria para guardar a nova solu��o
	nova_sol = malloc(sizeof(int)*vert);
	if (nova_sol == NULL){
		printf("Erro na alocacao de memoria");
		exit(1);
	}

	// Avalia solu��o inicial
	custo = calcula_fit(sol, mat, vert);

	for (i = 0; i < num_iter; i++){
		// Gera solu��o vizinha
		gera_vizinho(sol, nova_sol, vert, 1);

		//Se a solu��o vizinha for melhor, passa a ser essa a solu��o
		custo_viz = calcula_fit(nova_sol, mat, vert);
		if (custo_viz > custo){
			memcpy(sol, nova_sol, sizeof (int)*vert);
			custo = custo_viz;
		}
	}

	// Liberta a mem�ria usada para guardar a nova solu��o
	free(nova_sol);
	// Devolve o custo da melhor solu��o encontrada
	return custo;
}