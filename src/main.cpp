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

  int number_runs = 10;
  if (KATTIS) number_runs = 1;
  double average_cost = 0;

  // number of cities
  int n;

  // read the input from stdin
  vector<city_t> input = read_stdin(n);

  for (int run = 0; run < number_runs; run++) {

  // setup timer
  clock_t current_t, start_t = clock();

  // calculate a distance matrix
  int **graph = distance_matrix(n, input);

  // find the minimum spanning tree
  int *mst = find_mst(n, graph);

  // build an adjacency list
  vector<int> *adj;

  int best_matching_cost = INT_MAX;
  vector<int> best_matching_path;

  vector<int> matching_costs {};
  bool randomize = false;
  
  do {
    vector<int>* adj_copy = build_adjacency(n,mst);

    // // find graph's perfect matching
    int cost = perfect_matching(n, adj_copy, graph, randomize); // TODO: improve?

    // make first run completly greedy and the rest a bit random 
    randomize = true;

    if (!KATTIS) matching_costs.push_back(cost);

    if (cost < best_matching_cost) {
      adj = adj_copy;
      best_matching_cost = cost;
    }
    current_t = clock();
  } while (TIME_FOURTY(current_t, start_t));

  // determine euler circuit
  vector<int> e_circuit = euler_circuit(adj);

  // draw hamiltonian cycle
  vector<int> path = hamilton_cycle(n, graph, e_circuit);

  // optimise cycle until timeout=2sec
  KOPT opt = KOPT(graph, path);

  vector<int> best_path = opt.get_path();
  int curr_cost = opt.path_cost();
  int previous_cost = 0;

  std::random_device rd;
  default_random_engine rng(rd());

  vector<int> cost_array{};

  bool shuffle = false;

  do
  {

    if (shuffle)
    {
      opt.shuffle_tour(rng);
      shuffle = false;
    }

    opt.two(start_t, n);
    opt.two_half(start_t, n);
    opt.three(start_t, n);

    int cost = opt.path_cost();

    if (!KATTIS)
      cost_array.push_back(cost);

    if (cost < curr_cost)
    {
      best_path = opt.get_path();
      curr_cost = cost;
      // cout << "New best path: " << cost << endl;
    }

    if (cost >= previous_cost)
      shuffle = true;
    previous_cost = cost;

    current_t = clock();
  } while (TIME_MAX(current_t, start_t));

  // opt.set_path(best_path);

  // do {
  //   opt.two(start_t, n);
  //   opt.two_half(start_t, n);
  //   opt.three(start_t, n);

  //   current_t = clock();
  // } while(TIME_MAX(current_t, start_t));

  // for (int i = 0; i < int(best_path.size()); i++) assert(best_path[i] == real_best_path[i]);

  average_cost += print_path(best_path, graph, KATTIS);

  // write cost into file
  if (!KATTIS)
  {
    std::ofstream outFile("costs.dat");
    for (const auto &e : cost_array)
      outFile << e << "\n";

    std::ofstream outFile2("matching.dat");
    for (const auto &e :matching_costs) outFile2 << e << "\n";
    }
  }

  if (!KATTIS && number_runs > 1) {
    average_cost = average_cost / number_runs;
    cout << "Average cost: " << int(average_cost) << endl;
  }

  return 0;
}