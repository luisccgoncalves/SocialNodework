#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents)
{
	int i, x1, x2;

	// Realiza popsize torneios
	for (i = 0; i < d.popsize; i++)
	{
		x1 = random_l_h(0, d.popsize - 1);
		do
			x2 = random_l_h(0, d.popsize - 1);
		while (x1 == x2);
		if (pop[x1].fitness > pop[x2].fitness)		// Problema de maximizacao
			parents[i] = pop[x1];
		else
			parents[i] = pop[x2];
	}
}

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament_geral(pchrom pop, struct info d, pchrom parents)
{
	int i, j, k, sair, best, *pos;

	pos = malloc(d.tsize * sizeof(int));
	// Realiza popsize torneios
	for (i = 0; i < d.popsize; i++)
	{
		// Seleciona tsize soluções diferentes para entrarem em torneio de seleção
		for (j = 0; j < d.tsize; j++)
		{
			do
			{
				pos[j] = random_l_h(0, d.popsize - 1);
				// Verifica se a nova posição escolhida é igual a alguma das outras posições escolhidas
				sair = 0;
				for (k = 0; k < j; k++)
				{
					if (pos[k] == pos[j])
						sair = 1;
				}
			} while (sair);
			// Guarda a posição da melhor solução de todas as que entraram em torneio
			if (j == 0 || pop[pos[j]].fitness > pop[pos[best]].fitness)		// Problema de maximizacao
				best = j;
		}
		parents[i] = pop[pos[best]];
	}
	free(pos);
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
	// Recombinação com um ponto de corte
	//crossover(parents, d, offspring);
	// Recombinação com dois pontos de corte
	// Exercício 4.4(a)
	recombinacao_dois_pontos_corte(parents, d, offspring);
	// Recombinação uniforme
	// Exercício 4.4(b)
//	recombinacao_uniforme(parents, d, offspring);
	// Mutação binária
	mutation(offspring, d);
	// Mutação por troca
	// Exercício 4.3
	//mutacao_por_troca(offspring, d);
}

// Preenche o vector descendentes com o resultado da operação de recombinação com um ponto de corte
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void crossover(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point;

	for (i = 0; i < d.popsize - (d.popsize % 2); i += 2)
	{
		if (rand_01() < d.pr)
		{
			point = random_l_h(0, d.numGenes - 1);
			for (j = 0; j < point; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i + 1].p[j] = parents[i + 1].p[j];
			}
			for (j = point; j < d.numGenes; j++)
			{
				offspring[i].p[j] = parents[i + 1].p[j];
				offspring[i + 1].p[j] = parents[i].p[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}

// Preenche o vector descendentes com o resultado da operação de recombinação com dois pontos de corte
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void recombinacao_dois_pontos_corte(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point1, point2;

	for (i = 0; i < d.popsize - (d.popsize % 2); i += 2)
	{
		if (rand_01() < d.pr)
		{
			point1 = random_l_h(0, d.numGenes - 2);
			point2 = random_l_h(point1 + 1, d.numGenes - 1);
			for (j = 0; j < point1; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i + 1].p[j] = parents[i + 1].p[j];
			}
			for (j = point1; j < point2; j++)
			{
				offspring[i].p[j] = parents[i + 1].p[j];
				offspring[i + 1].p[j] = parents[i].p[j];
			}
			for (j = point2; j < d.numGenes; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i + 1].p[j] = parents[i + 1].p[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}

// Preenche o vector descendentes com o resultado da operação de recombinação uniforme
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void recombinacao_uniforme(pchrom parents, struct info d, pchrom offspring)
{
	int i, j;

	for (i = 0; i < d.popsize; i += 2)
	{
		if (rand_01() < d.pr)
		{
			for (j = 0; j < d.numGenes; j++)
			{
				if (flip() == 1)
				{
					offspring[i].p[j] = parents[i].p[j];
					offspring[i + 1].p[j] = parents[i + 1].p[j];
				}
				else
				{
					offspring[i].p[j] = parents[i + 1].p[j];
					offspring[i + 1].p[j] = parents[i].p[j];
				}
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}

// Mutação binária com vários pontos de mutação
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutation(pchrom offspring, struct info d)
{
	int i, j;

	for (i = 0; i < d.popsize; i++)
		for (j = 0; j < d.numGenes; j++)
			if (rand_01() < d.pm)
				offspring[i].p[j] = !(offspring[i].p[j]);
}

// Mutação por troca
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutacao_por_troca(pchrom offspring, struct info d)
{
	int a1, a2;
	for (int i = 0; i < d.popsize; i++) {
		if (rand_01() < d.pm) {
			int timeOut = 0;
			a1 = random_l_h(0, d.numGenes - 1);
			do {
				a2 = random_l_h(0, d.numGenes - 1);
				timeOut++;
			} while (a2 == a1 && offspring[i].p[a1] == offspring[i].p[a2] && timeOut < d.popsize);
			offspring[i].p[a1] = !offspring[i].p[a1];
			offspring[i].p[a2] = !offspring[i].p[a2];
		}
	}
}

void gera_vizinho(int a[], int b[], int n, int viz) {

	int i, j;
	int running = 1;

	// Copia a solução atual para a solução vizinha
	memcpy(b, a, sizeof(int)*n);

	//Não podem haver mais vizinhos que vértices 
	if (viz > n)
		viz = n;

	int *vizMat = malloc((sizeof(int))*viz);

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

int calcula_fit(int a[], int *mat, int vert)
{
	int colisao = 0, total = 0;
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

int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
	int *nova_sol, custo, custo_viz, i;

	// Aloca espaço em memória para guardar a nova solução
	nova_sol = malloc(sizeof(int)*vert);
	if (nova_sol == NULL) {
		printf("Erro na alocacao de memoria");
		exit(1);
	}

	// Avalia solução inicial
	custo = calcula_fit(sol, mat, vert);

	for (i = 0; i < num_iter; i++) {
		// Gera solução vizinha
		gera_vizinho(sol, nova_sol, vert, 1);

		//Se a solução vizinha for melhor, passa a ser essa a solução
		custo_viz = calcula_fit(nova_sol, mat, vert);
		if (custo_viz > custo) {
			memcpy(sol, nova_sol, sizeof(int)*vert);
			custo = custo_viz;
		}

	}

	// Liberta a memória usada para guardar a nova solução
	free(nova_sol);
	// Devolve o custo da melhor solução encontrada
	return custo;
}