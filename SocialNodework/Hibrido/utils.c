#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

// Inicializa��o do gerador de n�meros aleat�rios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Leitura dos par�metros e dos dados do problema
// Par�metros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Par�metros de sa�da: Devolve a estrutura com os par�metros
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

	//Vai lendo linhas e descartando-as, se a linha come�ar por p, grava os vertices e arestas e sai do ciclo
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
	// Devolve a estrutura com os par�metros
	return inf;
}

// Simula o lan�amento de uma moeda, retornando o valor 0 ou 1
int flip()
{
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Par�metro de entrada: Estrutura com par�metros do problema
// Par�metro de sa�da: Preenche da estrutura da popula��o apenas o vector bin�rio com os elementos que est�o dentro ou fora da mochila
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

// Actualiza a melhor solu��o encontrada
// Par�metro de entrada: populacao actual (pop), estrutura com par�metros (d) e a melhor solucao encontrada at� a gera��oo imediatamente anterior (best)
// Par�metro de sa�da: a melhor solucao encontrada at� a gera��o actual
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

// Escreve uma solu��o na consola
// Par�metro de entrada: populacao actual (pop) e estrutura com par�metros (d)
void write_best(chrom x, struct info d) {

	printf("\nBest individual: %4.1f\n", x.fitness);
	for (int i = 0; i < d.numGenes; i++)
		if (x.p[i])
			printf("%2d  ", i + 1);
	printf("\n");
}