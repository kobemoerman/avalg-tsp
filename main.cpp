#include "mst.hpp"
#include "utils.hpp"
#include "matching.hpp"
#include "euler.hpp"
#include "hamilton.hpp"
#include "opt.hpp"
#include <fstream>


int main (int argc, char **argv) {

  // setup timer
  clock_t current_t, start_t = clock();
  
  // number of cities
  int n;

  // read the input from stdin
  vector<city_t> input = read_stdin(n);

  // calculate a distance matrix
  int** graph = distance_matrix(n, input);
  int** graph_copy = init2Darray(n);

  // find the minimum spanning tree
  int* mst = find_mst(n, graph);

  vector<int> e_circuit;
  vector<int> path;
  vector<int> best_path;

  int best_matching_cost = INT_MAX;
  vector<int> best_matching_path;

  vector<int> matching_costs {};
  bool randomize = false;
  
  do {

    // create deep copy of graph (maybe use memcopy)
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++){
        graph_copy[j][k] = graph[j][k];
      }
    }

    vector<int>* adj_copy = build_adjacency(n,mst);

    // // find graph's perfect matching
    perfect_matching(n, adj_copy, graph_copy, randomize); // TODO: improve?

    // make first run completly greedy and the rest a bit random 
    randomize = true;

    // // determine euler circuit
    e_circuit = euler_circuit(adj_copy);
    vector<int> e_circuit_copy = e_circuit;

    // // draw hamiltonian cycle
    path = hamilton_cycle(n, graph_copy, e_circuit_copy);

    int cost = 0;
    for (uint i = 0; i < path.size()-1; i++) {
      cost += graph_copy[path[i]][path[i+1]];
    }
    cout << cost << endl;
    matching_costs.push_back(cost);
    if (cost < best_matching_cost) best_matching_path = path;
    current_t = clock();
  } while (TIME_TEN(current_t, start_t));
  

  // optimise cycle until timeout=2sec
  KOPT opt = KOPT(graph, best_matching_path);
  opt.two(start_t, n);
  opt.two_half(start_t, n);
  
  int curr_cost = opt.path_cost();
  int previous_cost = 0;

  std::random_device rd;
  default_random_engine rng(rd());

  vector<int> cost_array {};

  bool shuffle = false;

  do {

    if (shuffle) {opt.shuffle_tour(rng); shuffle = false;}

    opt.two(start_t, n);
    opt.two_half(start_t, n);
    //opt.three(start_t, n);

    cost_array.push_back(opt.path_cost());
    int cost = opt.path_cost();
    // cout << cost << endl;
    if (cost < curr_cost) {
      best_path = opt.get_path(); 
      opt.set_path(best_path);
      curr_cost = cost;
    }

    if (cost >= previous_cost) shuffle = true;
    previous_cost = cost;

    current_t = clock();
  } while(TIME_MAX(current_t, start_t));

  // print_path(best_path, graph);

  // write cost into file
  std::ofstream outFile("costs.dat");
  for (const auto &e : cost_array) outFile << e << "\n";

  std::ofstream outFile2("matching.dat");
  for (const auto &e :matching_costs) outFile2 << e << "\n";

  return 0;
}