#include "matching.hpp"

/**
  * @Info:    Transforms adjacency list to include a perfect matching list using a greedy algorithm. 
  *           The result is the adjacency list unioned with the perfect matching set (T U M).
  *           Greedy approximation algorithm.
  */
void perfect_matching(int n, vector<int> *&adj, int **g)
{
  int len;

  vector<int>::iterator i, first, last, closest;
  vector<int> odd_v = odd_vertex(n, adj);

  while (!odd_v.empty())
  {
    len = INT_MAX;
    first = odd_v.begin();
    last = odd_v.end();

    for (i = first + 1; i != last; i++)
    {
      if (g[*first][*i] < len)
      {
        len = g[*first][*i];
        closest = i;
      }
    }

    adj[*first].push_back(*closest);
    adj[*closest].push_back(*first);

    odd_v.erase(closest);
    odd_v.erase(first);
  }
}

/**
  * @Info:    Finds all vertices with odd degree.
  * @Return:  Vertex vector.
  */
vector<int> odd_vertex(int n, vector<int> *adj)
{
  int i;

  vector<int> v;

  for (i = 0; i < n; i++)
  {
    if (adj[i].size() % 2 != 0)
    {
      v.push_back(i);
    }
  }

  return v;
}