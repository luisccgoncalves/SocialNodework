#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

float eval_individual(int sol[], struct info d, int *mat, int *v){

	int total = 0, colisao = 0;

	for (int i = 0; i < d.numGenes; i++) {
		if (sol[i]) {
			total++;					//Conta 1 n� na solu��o
			for (int j = 0; j < d.numGenes; j++)
				if (sol[j] && *(mat + i * d.numGenes + j))
					colisao++;			//Se o n� tiver uma colis�o com outro membro da solu��o, conta uma colis�o
		}
	}

	if (colisao == 0) {
		*v = 1;
		return total;		//Se n�o houverem colis�es, � uma solu��o v�lida e devolve o n� de n�s do grupo
	}
	else {
		*v = 0;
		return -colisao;	//Se houverem penaliza a qualidade.
	}
}

//Procura uma colis�o e remove esse n� da solu��o
void repara(int sol[], int max, int *mat) {
	
	for (int i = 0; i < max; i++) {
		if (sol[i]) {
			for (int j = 0; j < max; j++)
				if (sol[j] && *(mat + i * max + j)) {
					sol[i] = 0;
					return;
				}
		}
	}
}

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate(pchrom pop, struct info d, int *mat){

	int rep = 0;

	for (int i = 0; i < d.popsize; i++) {

		do {
			pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
			if (pop[i].valido == 0 && rep)
				repara(pop[i].p, d.numGenes, mat);
		} while (pop[i].valido == 0 && rep);
	}
}
