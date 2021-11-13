#include <bits/stdc++.h>
using namespace std;
#include "main.hpp"
#include <random>


class KOPT {
  int** g;
  vector<int> p;
  int path_length;

  void swap_u (int i, int k);
  void swap_d (int i, int k);
  void reverse_segment_if_better(int i, int j, int k); 
  int dist (int i, int k) { return g[p[i]][p[k]]; }

  void two_opt_swap(int n, int start, int end) {
    while (end - start > 0) {
      int tmp = p[start % n];
      p[start++ % n] = p[end % n];
      p[end-- % n] = tmp;
    }
  }

  public:
    KOPT (int** graph, vector<int> path) {
      g = graph;
      p = path;

      path_length = path.size();
    }

    vector<int> get_path () { return p; }
    void two (clock_t t, int n);
    void two_half (clock_t t, int n);
    void three (clock_t t, int n);
    void shuffle_tour(default_random_engine rng);
    int path_cost();
    void set_path(vector<int> path) {
      p = path;
    }
};