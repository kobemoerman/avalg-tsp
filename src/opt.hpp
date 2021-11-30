#include <bits/stdc++.h>
using namespace std;
#include "main.hpp"
#include <random>

class LK_HEUR
{
  int **graph;
  vector<int> path;
  int n;

  pair<int, int> make_sorted_pair(int x, int y);
  void reverse_segment(int start, int end);

public:
  LK_HEUR(int **g, vector<int> p) {
    graph = g;
    path = p;

    n = p.size();
  }

  double path_cost();
  void make_move(int start);
  vector<int> get_path() { return path; }
  void set_path(vector<int> p) { path = p; }
};
