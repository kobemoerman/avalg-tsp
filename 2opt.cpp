#include "2opt.hpp"

// https://en.wikipedia.org/wiki/2-opt

void two_opt_swap(int n, vector<int> &path, int start, int end) {
    while (end - start > 0) {
        int temp = path[start % n];
        path[start % n] = path[end % n];
        path[end % n] = temp;
        start++;
        end--;
    }
}

int is_path_shorter(int **g, int i, int di, int k, int dk) {
    return (g[i][k] + g[di][dk]) - (g[i][di] + g[k][dk]);
}

void two_opt (clock_t t, int n, int** g, vector<int>& p) {
  int delta;
  int i, k, di, dk;

  for (i = 0; i < n; i++) {
    di = p[(i+1)%n];
    for (k = i + 1; (k + 1) % n != i; k++) {
      dk = p[(k+1)%n];

      if (TIME_U(clock(), t)) return;

      delta = g[p[i]][p[k%n]] + g[di][dk] - (g[p[i]][di] + g[p[k%n]][dk]);

      if (delta < 0) {
        two_opt_swap(n, p, i+1, k); 
      }
    }
  }
}