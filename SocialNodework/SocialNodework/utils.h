#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* init_dados(char *nome, int *n, int *iter);

void seed_rand();
int random_l_h(int min, int max);
float rand_01();

#endif