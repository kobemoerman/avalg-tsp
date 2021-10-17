#include "mst.hpp"
#include "utils.hpp"
#include "matching.hpp"
#include "euler.hpp"
#include "hamilton.hpp"
#include "opt.hpp"

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
  perfect_matching(n, adj, graph); // TODO: improve?

  // determine euler circuit
  vector<int> e_circuit = euler_circuit(adj);

  // draw hamiltonian cycle
  vector<int> path = hamilton_cycle(n, graph, e_circuit);

  // optimise cycle until timeout=2sec
  KOPT opt = KOPT(graph, path);
  do {
    current_t = clock();

    opt.two(start_t, n);
    opt.two_half(start_t, n);
    // TODO: add 3-opt

  } while(TIME_D(current_t, start_t));

  print_path(opt.get_path(), graph);

  return 0;
}