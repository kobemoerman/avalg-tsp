#include "opt.hpp"

double LK_OPT::lin_kernighan(double curr_cost) {
  vector<int> checked_neighbors;

  while (checked_neighbors.size() < n) {
    vector<int> new_tour;
    int closest = findClosestToEnd(checked_neighbors, path[n-1]);
    int next_closest;

    if (closest != -1) {
      checked_neighbors.push_back(closest);
      for (int i = 0; i < n; i++) {
        new_tour.push_back(path[i]);
        if (path[i] == closest) {
          next_closest = path[(i+1)%n];
          break;
        }
      }
      for (int i = n-1; path[i] != next_closest; i--) {
        new_tour.push_back(path[i]);
      }
      new_tour.push_back(next_closest);

      double new_cost = path_cost(new_tour);

      if (new_cost < curr_cost) {
        return new_cost;
      } else {
        path = new_tour;
        curr_cost = new_cost;
      }
    } else {
      return curr_cost;
    }
  }
}

bool LK_OPT::alreadyCheckedNeighbor(vector<int> neighbors, int id){
	for(int i = 0; i < neighbors.size(); i++){
		if (neighbors[i] == id) return true;
	}
	return false;
}

int LK_OPT::findClosestToEnd(vector<int> neighbors, int end){
  int i, j;
  int min_idx = -1;
  int dist = INT_MAX;

  for (i = 0; i < n; i++) {
    if (graph[end][i] < dist && i != end && !alreadyCheckedNeighbor(neighbors, i)) {
      dist = graph[end][i];
      min_idx = i;
    }
  }

  return min_idx;
}


double LK_OPT::path_cost (vector<int> p) {
  uint i;
  long cost = 0;

  for (i = 0; i < path.size(); i++)
    cost += graph[p[i]][p[i + 1]];

  // cout << "# " << cost << endl;
  return cost;
}
