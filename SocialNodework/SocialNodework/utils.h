#pragma warning(disable:4996)
#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>

void file2adjMat(int **mainAdjMat, int *vertices, int *arestas, char *filename);
void adjMat2file(const int *adjMat, int vertices, int arestas, const char *filename);
void populateSolution(int *solution, int vertices);
void printSolution(int *solution, int vertices);
void seed_rand();
int random_l_h(int min, int max);
float rand_01();
int flipCoin();
int calcula_fit(int a[], int *mat, int vert);
void createCSV(	int		runs, 
				int		maxIterations, 
				int		vertices, 
				float	mbf, 
				int		bestCusto, 
				double	timeTaken, //
				const char *filename, //
				const char *outputDir);//
#endif