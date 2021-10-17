#include "mst.hpp"
#include "utils.hpp"
#include "matching.hpp"
#include "euler.hpp"
#include "hamilton.hpp"

int main (int argc, char **argv) {
  
  // number of cities
  int n;

  // read the input from stdin
  vector<city_t> input = read_stdin(n);

  // calculate a distance matrix
  int** graph = distance_matrix(n, input);

  // find the minimum spanning tree
  int* mst = find_mst(n, graph);

  // build an adjacency list
  vector<int>* adj = build_adjacency(n, mst);

  // find graph's perfect matching
  perfect_matching(n, adj, graph);

  // determine euler circuit
  vector<int> e_circuit = euler_circuit(adj);

  // draw hamiltonian cycle
  hamilton_cycle(n, graph, e_circuit);

  return 0;
}