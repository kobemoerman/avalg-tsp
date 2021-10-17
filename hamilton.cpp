#include "hamilton.hpp"

void hamilton_cycle (int n, int** g, vector<int> cycle) {
  int i, dist = 0;
  bool visit[n];

  // all vertices can be visited
  for (i = 0; i < n; i++) visit[i] = true;

  visit[cycle.front()] = false;
  vector<int>::iterator v = next(cycle.begin(), 1);

  cout << "(" << cycle.front() << ") -> ";

  // continue until the end of the path
  while (v != cycle.end()) {
    // the current vertex has not been visited
    if (visit[*v]) {
      cout << "(" << *v << ") -> ";
      dist += g[*v][*(v+1)];
      visit[*v] = false;
      v = next(v, 1);
    } else { // the current vertex has been visited so remove it
      v = cycle.erase(v);
    }
  }

  cout << "(" << *v << ")" << endl;
  dist += g[*v][*(v+1)];
  cout << "#cost: " << dist << endl;
}