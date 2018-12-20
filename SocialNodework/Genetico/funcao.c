#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

// Calcula a qualidade de uma solução
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, int *mat, int *v){

	int total = 0, colisao = 0;

	for (int i = 0; i < d.numGenes; i++) {
		if (sol[i]) {
			total++;					//Conta 1 nó na solução
			for (int j = 0; j < d.numGenes; j++)
				if (sol[j] && *(mat + i * d.numGenes + j))
					colisao++;			//Se o nó tiver uma colisão com outro membro da solução, conta uma colisão
		}
	}

	if (colisao == 0) {
		*v = 1;
		return total;		//Se não houverem colisões, é uma solução válida e devolve o nº de nós do grupo
	}
	else {
		*v = 0;
		return -colisao;	//Se houverem penaliza a qualidade.
	}
}

// Avaliacao da população
// Parâmetros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parâmetros de saída: Preenche pop com os valores de fitness e de validade para cada solução
void evaluate(pchrom pop, struct info d, int *mat)
{

	for (int i = 0; i < d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
}
