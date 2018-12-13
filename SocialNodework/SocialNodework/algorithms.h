#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include "utils.h"

//void bruteForce(int *solution[MAXSIZE], int adjMat[MAXSIZE][MAXSIZE], int vertices, int arestas);

void gera_vizinho(int a[], int b[], int n, int viz);
int trepa_colinas(int sol[], int *mat, int vert, int num_iter);


#endif