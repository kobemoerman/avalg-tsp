#include "opt.hpp"

// https://en.wikipedia.org/wiki/2-opt

void KOPT::two (clock_t t, int n) {
  int i, k, delta;

  for (i = 0; i < n; i++) {
    for (k = i+3; k < n; k++) {
      if (TIME_U(clock(), t)) return;

      delta = dist(i, k-1) + dist(i+1, k) - (dist(i, i+1) + dist(k-1, k));

      if (delta < 0) {
        reverse(p.begin() + i + 1, p.begin() + k);
      }
    }
  }
}

void KOPT::two_half (clock_t t, int n) {
  int i, k, v1, v2;

  for (i = 0; i < n; i++) {
    for (k = i+3; k < n; k++) {
      if (TIME_U(clock(), t)) return;
      
      // in: A-B-C-D-E | try: A-C-D-B-E
      v1 = dist(i, i+1) + dist(i+1, i+2) + dist(k-1, k);
      v2 = dist(i, i+2) + dist(k-1, i+1) + dist(i+1, k);

      if (v2 < v1) swap_u(i, k);

      // in: A-B-C-D-E | try: A-D-B-C-E
      v1 = dist(i, i+1) + dist(k-2, k-1) + dist(k-1, k);
      v2 = dist(i, k-1) + dist(k-1, i+1) + dist(k-2, k);

      if (v2 < v1) swap_d(i,k);
    } 
  }
}

void KOPT::swap_u (int i, int k) {
  int v;
  int tmp = p[i+1];
  for (v = i+2; v < k; v++) {
    p[v-1] = p[v];
  }
  p[k-1] = tmp;
}

void KOPT::swap_d (int i, int k) {
  int v;
  int tmp = p[k-1];
  for (v = k-2; v > i; v--) {
    p[v+1] = p[v];
  }
  p[i+1] = tmp;
}