#include "2opt.hpp"

// https://en.wikipedia.org/wiki/2-opt

void two_opt (clock_t t, int n, int** g, vector<int>& p) {
  int delta;
  int i, k, di, dk;

  for (i = 0; i < n - 1; i++) {
    di = (i + 1) % n;
    for (k = i+1; k < n; k++) {
      dk = (k + 1) % n;

      if (TIME_U(clock(), t)) return;

      delta = (g[i][k]+g[di][dk]) - (g[i][di]+g[k][dk]);

      if (delta < 0) {
        reverse(begin(p)+i, begin(p)+k+1);
      }
    }
  }
}