#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

// Inicialização do gerador de números aleatórios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Leitura dos parâmetros e dos dados do problema
// Parâmetros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Parâmetros de saída: Devolve a estrutura com os parâmetros
struct info init_data(char *filename, int **mainMat)
{
	struct  info inf;
	FILE    *f;
	int     *mat, x, y;
	char	line[100];

	f = fopen(filename, "rt");
	if (!f)
	{
		printf("File not found\n");
		exit(1);
	}

	//Vai lendo linhas e descartando-as, se a linha começar por p, grava os vertices e arestas e sai do ciclo
	while (fgets(line, sizeof line, f) != NULL) {

		if (line[0] == 'p') {
			sscanf(line, "%*s %*s %d %*d", &inf.numGenes);
			inf.popsize = inf.numGenes;
			break;
		}

	}

	if (inf.numGenes > MAX_OBJ)
	{
		printf("Number of vertices is superior to MAX_OBJ\n");
		exit(1);
	}

	mat = malloc(sizeof(int)*(inf.numGenes)*(inf.numGenes));
	if (!mat) {
		printf("Erro de memoria!\n");
		exit(1);
	}

	memset(mat, 0, sizeof(int)*(inf.numGenes)*(inf.numGenes));

	while (fgets(line, sizeof line, f) != NULL) {

		if (line[0] == 'e') {
			sscanf(line, "%*s %d %d", &x, &y);
			*(mat + (inf.numGenes)*(y - 1) + (x - 1)) = 1;
			*(mat + (inf.numGenes)*(x - 1) + (y - 1)) = 1;
		}
	}

	*mainMat = mat;

	fclose(f);
	// Devolve a estrutura com os parâmetros
	return inf;
}

// Simula o lançamento de uma moeda, retornando o valor 0 ou 1
int flip()
{
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Parâmetro de entrada: Estrutura com parâmetros do problema
// Parâmetro de saída: Preenche da estrutura da população apenas o vector binário com os elementos que estão dentro ou fora da mochila
pchrom init_pop(struct info d)
{
	int     i, j;
	pchrom  indiv;

	indiv = malloc(sizeof(chrom)*d.popsize);
	if (indiv == NULL)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	for (i = 0; i < d.popsize; i++)
	{
		for (j = 0; j < d.numGenes; j++)
			indiv[i].p[j] = flip();
	}
	return indiv;
}

// Actualiza a melhor solução encontrada
// Parâmetro de entrada: populacao actual (pop), estrutura com parâmetros (d) e a melhor solucao encontrada até a geraçãoo imediatamente anterior (best)
// Parâmetro de saída: a melhor solucao encontrada até a geração actual
chrom get_best(pchrom pop, struct info d, chrom best)
{
	int i;

	for (i = 0; i < d.popsize; i++)
	{
		if (best.fitness < pop[i].fitness)
			best = pop[i];
	}
	return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
	return ((float)rand()) / RAND_MAX;
}

// Escreve uma solução na consola
// Parâmetro de entrada: populacao actual (pop) e estrutura com parâmetros (d)
void write_best(chrom x, struct info d) {

	printf("\nBest individual: %4.1f\n", x.fitness);
	for (int i = 0; i < d.numGenes; i++)
		if (x.p[i])
			printf("%2d  ", i + 1);
	printf("\n");
}