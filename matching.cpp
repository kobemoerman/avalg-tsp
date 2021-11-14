#include "matching.hpp"
#include <random>

/**
  * @Info:    Transforms adjacency list to include a perfect matching list using a greedy algorithm. 
  *           The result is the adjacency list unioned with the perfect matching set (T U M).
  *           Greedy approximation algorithm.
  */
int perfect_matching(int n, vector<int> *&adj, int **g, bool randomness)
{
  int len;
  int total_cost = 0;

  vector<int>::iterator i, first, last, closest;
  vector<int> odd_v = odd_vertex(n, adj);

  if (randomness) {
    random_shuffle(odd_v.begin(),odd_v.end());
  }

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

    total_cost += len;

    adj[*first].push_back(*closest);
    adj[*closest].push_back(*first);

    odd_v.erase(closest);
    odd_v.erase(first);
  }
  return total_cost;
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