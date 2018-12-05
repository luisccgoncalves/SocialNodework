#include "algorithms.h"

//void bruteForce(int solution[MAXSIZE], int adjMat[MAXSIZE][MAXSIZE], int vertices, int arestas) {
//
//	int pos = 0;
//	int adjList[MAXSIZE][MAXSIZE] = { 0 };
//	int curSol[MAXSIZE] = { 0 };
//
//	for (int i = 0; i < vertices; i++) {
//		for (int j = 0; j < vertices; j++) {
//			if(adjMat[i][j]==0)
//				adjList[i][pos++] = j+1;
//		}
//
//		//for (int j = 0; j < pos; j++)
//		//	printf("%d, ", curSol[j]);
//		//printf("\n");
//
//		pos = 0;
//
//	}
//	for (int i = 0; i < vertices; i++) {
//		for (int j = 0;adjList[i][j]!=0; j++) {
//			printf("%d, ", adjList[i][j]);
//		}
//		printf("\n");
//	}
//}