#include <bits/stdc++.h>
using namespace std;
#include "main.hpp"
#include <random>

class LK_OPT
{
  int **graph;
  vector<int> path;
  int n;

  bool alreadyCheckedNeighbor(vector<int> neighbors, int id);
  int findClosestToEnd(vector<int> neighbors, int end);

public:
  LK_OPT(int **g, vector<int> p) {
    graph = g;
    path = p;

    n = p.size();
  }

  double path_cost(vector<int> p);
  double lin_kernighan(double curr_cost);
  vector<int> get_path() { return path; }
  void set_path(vector<int> p) { path = p; }
};
