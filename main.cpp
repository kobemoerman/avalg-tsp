#include "mst.hpp"
#include "utils.hpp"
#include "matching.hpp"
#include "euler.hpp"
#include "hamilton.hpp"
#include "2opt.hpp"

int main (int argc, char **argv) {

  // setup timer
  clock_t current_t, start_t = clock();
  
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
  vector<int> path = hamilton_cycle(n, graph, e_circuit);

  // optimise cycle until timeout=2sec
  do {
    current_t = clock();

    two_opt(n, graph, path);

  } while(double(current_t-start_t)/CLOCKS_PER_SEC < 1.99);

  return 0;
}