#include "hamilton.hpp"

vector<int> hamilton_cycle(int n, int **g, vector<int> cycle)
{
  int i, dist = 0;
  bool visit[n];
  vector<int> path;

  // all vertices can be visited
  for (i = 0; i < n; i++)
    visit[i] = true;

  visit[cycle.front()] = false;
  vector<int>::iterator v = next(cycle.begin(), 1);

  path.push_back(cycle.front());
  /*cout << "(" << cycle.front() << ") -> ";*/

  // continue until the end of the path
  while (v != cycle.end())
  {
    // the current vertex has not been visited
    if (visit[*v])
    {
      /* cout << "(" << *v << ") -> "; */
      path.push_back(*v);
      dist += g[*v][*(v + 1)];
      visit[*v] = false;
      v = next(v, 1);
    }
    else
    { // the current vertex has been visited so remove it
      v = cycle.erase(v);
    }
  }

  dist += g[*v][*(v + 1)];
  //cout << "(" << *v << ")" << endl;
  //cout << "#cost: " << dist << endl;

  return path;
}
