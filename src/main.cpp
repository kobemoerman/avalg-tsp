#include "mst.hpp"
#include "utils.hpp"
#include "matching.hpp"
#include "euler.hpp"
#include "hamilton.hpp"
#include "opt.hpp"

int main(int argc, char **argv)
{

  // setup timer
  clock_t current_t, start_t = clock();

  // number of cities
  int n;

  // read the input from stdin
  vector<city_t> input = read_stdin(n);

  // calculate a distance matrix
  int **graph = distance_matrix(n, input);

  // find the minimum spanning tree
  int *mst = find_mst(n, graph);

  // build an adjacency list
  vector<int> *adj = build_adjacency(n, mst);

  // find graph's perfect matching
  perfect_matching(n, adj, graph); // TODO: improve?

  // determine euler circuit
  vector<int> e_circuit = euler_circuit(adj);

  // draw hamiltonian cycle
  vector<int> path = hamilton_cycle(n, graph, e_circuit);

  // optimise cycle until timeout=2sec
  LK_OPT opt = LK_OPT(graph, path);

  double cost = opt.path_cost(path);

  // cout << "initial cost: " << cost << endl;

  vector<int> best_path = path;
  double new_cost;
  int freq, move;
  current_t = clock();
  for (freq = 0; TIME_MAX(current_t, start_t); current_t = clock(), freq++) {

    new_cost = opt.lin_kernighan(cost);

    if (new_cost < cost) {
      cost = new_cost;
      best_path = opt.get_path();
      // cout << "new cost: " << cost << endl;
    }
  }

  print_path(best_path, graph);



  // path = opt.get_path();
  // print_path(path, graph);

  return 0;
}
