#include "main.hpp"

int *find_mst(int n, int **g);
int mst_minKey(int n, int *key, bool *mstSet);
vector<int> *build_adjacency(int n, int *tree);
void print_adjacency(int n, vector<int> *adj);
void print_mst(int n, int parent[], int **graph);