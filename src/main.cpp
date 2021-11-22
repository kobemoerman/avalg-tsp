#include "mst.hpp"
#include "utils.hpp"
#include "matching.hpp"
#include "euler.hpp"
#include "hamilton.hpp"
#include "opt.hpp"
#include <fstream>

bool KATTIS = false;

int main(int argc, char **argv)
{

  // setup timer
  clock_t current_t, start_t = clock();

  // number of cities
  int n;
  int MAX_K = 10;

  // read the input from stdin
  vector<city_t> input = read_stdin(n);

  // calculate a distance matrix
  int **graph = distance_matrix(n, input);
  int **neighbor = createNeighborsMatrix(n, graph, MAX_K);

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
  KOPT opt = KOPT(graph, path, neighbor, MAX_K);

  int curr_cost = opt.path_cost();
  vector<int> best_path = opt.get_path();

  std::random_device rd;
  default_random_engine rng(rd());

  vector<int> cost_array{};

  int cost, freq, reg = 0;
  bool shuffle = false;

  current_t = clock();
  for (freq = 1; TIME_MAX(current_t, start_t); current_t = clock(), freq++) {
    if (shuffle)
    {
      // cout << "SHUFFLE" << endl;
      opt.shuffle_tour(rng);
      shuffle = false;
      reg++;
    }

    opt.two(start_t, n);
    opt.two_half(start_t, n);
    opt.three(start_t, n);

      cost = opt.path_cost();
    if (cost < curr_cost)
    {
      // cout << "BEST " << cost << endl;
      best_path = opt.get_path();
      curr_cost = cost;
      freq = 1;
    }

    if (freq%(5 + int(reg/10)) == 0) shuffle = true;
    
    if (!KATTIS) cost_array.push_back(cost);
  }

  // cout << curr_cost << endl;
  print_path(best_path, graph);

  // write cost into file
  if (!KATTIS)
  {
    std::ofstream outFile("costs.dat");
    for (const auto &e : cost_array)
      outFile << e << "\n";

    std::ofstream outFilePath("path.dat");
    for (const auto &e :best_path)
      outFilePath << e << "\n";
  }

  return 0;
}