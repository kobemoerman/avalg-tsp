#include "matching.hpp"

/**
  * @Info:    Transforms adjacency list to include a perfect matching list using a greedy algorithm. 
  *           The result is the adjacency list unioned with the perfect matching set (T U M).
  *           Greedy approximation algorithm.
  */
void perfect_matching(int n, vector<int> *&adj, int **g, bool randomness)
{
  int len;

  vector<int>::iterator i, first, last, closest;
  vector<int> odd_v = odd_vertex(n, adj);

  int save_n_best = int(n/10);
  std::vector<vector<int>::iterator> n_best(save_n_best);
  std::vector<int> n_length {INT_MAX};

  while (!odd_v.empty())
  {
    len = INT_MAX;
    first = odd_v.begin();
    last = odd_v.end();

    // pure greedy
    if (!randomness)
    {
      for (i = first + 1; i != last; i++)
      {
        if (g[*first][*i] < len)
        {
          len = g[*first][*i];
          closest = i;
        }
      }
    }
    else
    {
      n_best.clear();
      n_length.clear();

      for (i = first + 1; i != last; i++)
      {
        if (g[*first][*i] < len)
        {
          len = g[*first][*i];
          closest = i;
        }

        if (int(n_best.size()) < save_n_best) 
        {
          n_best.push_back(i);
          n_length.push_back(g[*first][*i]);
        }
        else if (g[*first][*i] < *max_element(begin(n_length), end(n_length))) {
          int max_idx = max_element(begin(n_length), end(n_length)) - begin(n_length);
          n_best[max_idx] = i;
          n_length[max_idx] = g[*first][*i];
        }
      }
      // select one of the n best 
      if (rand() % 100 < 10) {
        closest = n_best[rand() % n_best.size()];
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