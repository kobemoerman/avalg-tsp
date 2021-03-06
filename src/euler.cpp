#include "euler.hpp"

// http://www.graph-magics.com/articles/euler.php

/**
  * @Info:    Given an undirected find a path or circuit that passes through each edge exactly once.
  * @Return:  Vector path.
  */
vector<int> euler_circuit(vector<int> *adj)
{
  int n, v = 0;
  vector<int> circuit;
  stack<int> stack_e;

  // repeat until the current vertex has no more neighbors and the stack is empty
  while (!stack_e.empty() || adj[v].size() > 0)
  {
    // vertex has no neighbours
    if (adj[v].size() == 0)
    {
      circuit.push_back(v);
      v = pop_stack(stack_e);
    }
    else
    {
      stack_e.push(v);
      // take any neighbour and remove it
      n = adj[v].back();
      adj[v].pop_back();
      pop_neighbour(n, v, adj);
      // set neighbour as current vertex;
      v = n;
    }
  }

  circuit.push_back(v);

  return circuit;
}

/**
  * @Info:    Remove vertex v from neighbour n.
  */
void pop_neighbour(int n, int v, vector<int> *s)
{
  uint i = 0;

  do
  {
    if (s[n][i] == v)
    {
      s[n].erase(s[n].begin() + i);
      return;
    }
    i++;
  } while (i < s[n].size());

  return;
}

/**
  * @Info:    Pop stack and return value.
  * @Return:  Int at top of stack.
  */
int pop_stack(stack<int> &s)
{
  int res;

  res = s.top(), s.pop();

  return res;
}