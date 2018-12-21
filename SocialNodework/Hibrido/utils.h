struct info init_data(char *, int **mainMat);

pchrom init_pop(struct info);

chrom get_best(pchrom, struct info, chrom);

void write_best(chrom, struct info);

void init_rand();

int random_l_h(int, int);

float rand_01();

int flip();
