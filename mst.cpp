#include "mst.hpp"

/**
  * @Info:    Find the minimal spanning tree. Using Prim's algorithm.
  * @Return:  List of vertices. 
  */
int* find_mst (int n, int **g) {
  int i, u ,v;

  // values to choose min weight edge in cut
  int key[n];
  // constructed tree
  int* tree = (int *)malloc(n* sizeof(int));
  // visited vertices
  bool vsted[n];

  // initialisation
  for (i = 0; i < n; i++) {
    key[i] = INT_MAX;
    vsted[i] = false;
  }

  // first vertex is picked first
  key[0] = 0;
  tree[0] = -1;

  for (i = 0; i < n - 1; i++) {
    // pick closest min vertex not in tree
    u = mst_minKey(n, key, vsted);
    vsted[u] = true;

    // look at each vertex v adjacent to u that's not in MST
    for (v = 0; v < n; v++) {
      if (g[u][v] && vsted[v] == false && g[u][v] < key[v]) {
        // update tree index of v
        tree[v] = u;
        // update the key only if distance < key[v]
        key[v] = g[u][v];
      }
    }
  }

  return tree;
}

/**
  * @Info:    Make an adjacency list from the mst.
  * @Return:  Vector of lists.
  */
vector<int>* build_adjacency (int n, int* tree) {
  int v1, v2;
  vector<int>* list = new vector<int>[n];
  
  for (v1 = 1; v1 < n; v1++) {
    v2 = tree[v1];
    list[v1].push_back(v2), list[v2].push_back(v1);
  }

  return list;
}

/**
  * @Info:    MST helper function. Finds the neighbour with the smallest weight.
  * @Return:  Minimum weight index.
  */
int mst_minKey(int n, int *key, bool *mstSet) {
  int min = INT_MAX;
  int min_index = 0;
  for (int v = 0; v < n; v++) {
    if (!mstSet[v] && key[v] < min) {
      min = key[v];
      min_index = v;
  }
  }
  return min_index;
};

void print_adjacency (int n, vector<int>* adj) {
  for (int i = 0; i < n; i++) {
    cout << i << " -> ";
    for (auto x : adj[i]) cout << x << ", ";
    cout << "null" << endl;
  }
}

void print_mst(int n, int parent[], int **graph) {
  cout<<" Edge \tWeight\n";
  for (int i = 1; i < n; i++) {
    cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
  }
}