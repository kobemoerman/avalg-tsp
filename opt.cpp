#include "opt.hpp"

// https://en.wikipedia.org/wiki/2-opt
void KOPT::two (clock_t t, int n) {
  int i, k, di, dk, delta;

  for (i = 0; i < n; i++) {
    di = (i+1)%n;
    for (k = i+1; (k+1)%n != i; k++) {
      dk = (k+1)%n;

      // if (TIME_U(clock(), t)) return;

      delta = dist(i, k%n) + dist(di, dk) - (dist(i, di) + dist(k%n, dk));

      if (delta < 0) {
        two_opt_swap(n, i+1, k);
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

// https://en.wikipedia.org/wiki/3-opt
void KOPT::three (clock_t t, int n) {
  int delta = 0;
  int i, j, k;

  for (i = 0; i < n; i++) {
    for (j = i+2; j < n; j++) {
      for (k = j+2; k < n + (i>0); k++){

        delta += reverse_segment_if_better(i, j, k);

        if (TIME_U(clock(), t)) return;

        if (delta >= 0) return;
      }
    }
  }
}

int KOPT::reverse_segment_if_better(int i, int j, int k) {
  int z;

  int A = i-1;
  int B = i;
  int C = j-1;
  int D = j;
  int E = k-1;
  int F = k % p.size();

  int d0 = dist(A, B) + dist(C, D) + dist(E, F);
  int d1 = dist(A, C) + dist(B, D) + dist(E, F);
  int d2 = dist(A, B) + dist(C, E) + dist(D, F);
  int d3 = dist(A, D) + dist(E, B) + dist(C, F);
  int d4 = dist(F, B) + dist(C, D) + dist(E, A);

  if(d0 > d1) {
    reverse(p.begin()+i, p.begin()+j);
    return -d0 + d1;
  } else if(d0 > d2) {
    reverse(p.begin()+j, p.begin()+k); // FIX: k can be out of bounds
    return -d0 + d2;
  } else if(d0 > d4) {
    reverse(p.begin()+i, p.begin()+k); // FIX: k can be out of bounds
    return -d0 + d4;
  } else if(d0 > d3) {
    vector<int> tmp;
    for(z = j; z < k; z++) tmp.push_back(p[z]);
    for(z = i; z < j; z++) tmp.push_back(p[z]);
    for(z = i; z < k; z++) p[z] = tmp[z];
    
    return -d0 + d3;
  }

  return 0;
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