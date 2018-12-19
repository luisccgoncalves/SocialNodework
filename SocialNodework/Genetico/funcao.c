#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define GENERATIONS_TC  1000
#define PROBGERAVIZ     0.0

// Calcula a qualidade de uma solu��o
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, int *mat, int *v)
{//codigo da ficha 7 eval individual mudar 0 para 1 no 1� for
	//se for inv�lida, aplicar a repara��o

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

// Calcula a qualidade de uma solu��o com penaliza��o
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual_penalizado(int sol[], struct info d, int mat[][2], int *v)
{
	int     i;
	float   sum_weight, sum_profit;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i = 0; i < d.numGenes; i++)
	{
		// Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
			// Actualiza o peso total
			sum_weight += mat[i][0];
			// Actualiza o lucro total
			sum_profit += mat[i][1];
			// Obtem o melhor ro
			if (d.ro < (float)mat[i][1] / mat[i][0])
				d.ro = (float)mat[i][1] / mat[i][0];
		}
	}
	if (sum_weight > d.capacity)
	{
		// Solu��o inv�lida
		*v = 0;
		return sum_profit - (sum_weight - d.capacity)*d.ro; // Solucao com penaliza��o
	}
	else
	{
		// Solu��o v�lida
		*v = 1;
		return sum_profit;
	}
}

// Calcula a qualidade de uma solu��o com repara��o aleat�ria
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual_reparado1(int sol[], struct info d, int mat[][2], int *v)
{
	int     i;
	float   sum_weight, sum_profit;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i = 0; i < d.numGenes; i++)
	{
		// Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
			// Actualiza o peso total
			sum_weight += mat[i][0];
			// Actualiza o lucro total
			sum_profit += mat[i][1];
		}
	}
	// Processo de reparacao
	while (sum_weight > d.capacity)
	{
		// escolhe um objeto aleatoriamente
		i = random_l_h(0, d.numGenes - 1);
		// Se esse objeto estiver na mochila, retira-o e ajusta os somat�rios do peso e lucro
		if (sol[i] == 1)
		{
			sol[i] = 0;
			sum_weight -= mat[i][0];
			sum_profit -= mat[i][1];
		}
	}
	*v = 1;
	return sum_profit;
}

// Calcula a qualidade de uma solu��o com repara��o de acordo com uma heir�stica sofrega
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual_reparado2(int sol[], struct info d, int mat[][2], int *v)
{
	int     i, mv, pos;
	float   sum_weight, sum_profit;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i = 0; i < d.numGenes; i++)
	{
		// Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
			// Actualiza o peso total
			sum_weight += mat[i][0];
			// Actualiza o lucro total
			sum_profit += mat[i][1];
		}
	}
	// Processo de reparacao 2
	while (sum_weight > d.capacity)
	{
		pos = -1;
		for (i = 0; i < d.numGenes; i++)
		{
			if (sol[i] == 1)
			{
				if (pos == -1 || mv > mat[i][1])
				{
					mv = mat[i][1];
					pos = i;
				}
			}
		}
		sol[pos] = 0;
		sum_weight -= mat[pos][0];
		sum_profit -= mat[pos][1];
	}
	*v = 1;
	return sum_profit;
}

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate(pchrom pop, struct info d, int *mat)
{

	for (int i = 0; i < d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
}
