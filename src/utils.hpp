#include "main.hpp"

int **distance_matrix(int n, vector<city_t> v);
int eucledian(city_t city, city_t neighbour);
vector<city_t> read_stdin(int &n);
void print_matrix(int n, int **arr);
int print_path(vector<int> path, int **g, bool KATTIS);
int **init2Darray(int n);
void print_matrix(int n, int **arr);