#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS	5
#define DATA_DIR		"Data/"
#define OUTPUT_DIR		"Output/"

#define MUT_PROBAB		0.01	//[0-1]
#define RECOMB_PROB		0.3		//[0-1]
#define TORNAMNT_SZ		2
#define MAX_GEN			5


int main(int argc, char *argv[])
{
	char        nome_fich[100] = DATA_DIR;
	struct info EA_param;
	pchrom      pop = NULL, parents = NULL;
	chrom       best_run, best_ever;
	int         gen_actual, r, runs, i, inv, *mat;
	float       mbf = 0.0;

	// Lê os argumentos de entrada
	if (argc == 3)
	{
		runs = atoi(argv[2]);
		strcat(nome_fich, argv[1]);
	}
	else
		// Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
		if (argc == 2)
		{
			runs = DEFAULT_RUNS;
			strcat(nome_fich, argv[1]);
		}
	// Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
		else
		{
			runs = DEFAULT_RUNS;
			//printf("Nome do Ficheiro: ");
			//scanf("%49[^\n]s", &nome_fich);
			strcat(nome_fich, "c-fat500-1.clq");
			//strcat(nome_fich, "inst_teste.txt");
		}
	// Se o número de execuções do processo for menor ou igual a 0, termina o programa
	if (runs <= 0)
		return 0;
	//Inicializa a geração dos números aleatórios
	init_rand();
	// Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
	EA_param = init_data(nome_fich, &mat);

	//EA_param.pm = (float) MUT_PROBAB;
	//EA_param.pr = (float) RECOMB_PROB;
	FILE *f = fopen("c-fat500-1-250-500.clq.csv","w");
	float inc = 0.01;
	EA_param.tsize = TORNAMNT_SZ;
	EA_param.numGenerations = MAX_GEN;

	fprintf(f, ";");
	for(float i=0;i<=1+inc;i+= inc)
		fprintf(f, "%.2f;", i);
	fprintf(f, "\n");

	for (EA_param.pm = 0.5; EA_param.pm <= 1; EA_param.pm += inc) {
		fprintf(f, "%.2f;", EA_param.pm);
		for (EA_param.pr = 0; EA_param.pr <= 1+inc; EA_param.pr += inc) {
			
			// Faz um ciclo com o número de execuções definidas
			for (r = 0, mbf=0; r < runs; r++)
			{
				//printf("Repeticao %d\n", r + 1);
				// Geração da população inicial
				pop = init_pop(EA_param);
				// Avalia a população inicial
				evaluate(pop, EA_param, mat);
				// Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
				best_run = pop[0];
				// Encontra-se a melhor solução dentro de toda a população
				best_run = get_best(pop, EA_param, best_run);
				// Reserva espaço para os pais da população seguinte
				parents = malloc(sizeof(chrom)*EA_param.popsize);
				// Caso não consiga fazer a alocação, envia aviso e termina o programa
				if (parents == NULL)
				{
					printf("Erro na alocacao de memoria\n");
					exit(1);
				}
				// Ciclo de optimização
				gen_actual = 1;
				while (gen_actual <= EA_param.numGenerations)
				{

					// Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
					tournament(pop, EA_param, parents);

					// Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
					genetic_operators(parents, EA_param, pop);

					// Avalia a nova população (a dos filhos)
					evaluate(pop, EA_param, mat);

					// Actualiza a melhor solução encontrada
					best_run = get_best(pop, EA_param, best_run);
					gen_actual++;
				}
				// Contagem das soluções inválidas
				for (inv = 0, i = 0; i < EA_param.popsize; i++)
					if (pop[i].valido == 0)
						inv++;
				// Escreve resultados da repetição que terminou
				//printf("\nRepeticao %d:", r);
				//write_best(best_run, EA_param);
				//printf("\nPercentagem Invalidos: %f\n", 100 * (float)inv / EA_param.popsize);
				mbf += best_run.fitness;
				if (r == 0 || best_run.fitness > best_ever.fitness)
					best_ever = best_run;
				// Liberta a memória usada
				free(parents);
				free(pop);
			}
			fprintf(f, "%.2f;",mbf/r);
			printf("%.2f %.2f %.2f\n", EA_param.pm, EA_param.pr, mbf / r);
		}
		fprintf(f, "\n");
	}


	fclose(f);
	// Escreve resultados globais
	printf("\n\nMBF: %f\n", mbf / r);
	printf("\nMelhor solucao encontrada");
	write_best(best_ever, EA_param);
	return 0;
}
