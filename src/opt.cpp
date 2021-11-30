#include "opt.hpp"


void LK_HEUR::make_move(int start) {
  vector<int> opt = path;

  pair<int, int> broken_edge;
  set<pair<int,int> > broken_set, joined_set;

  double g_local, g_opt_local, g_opt = 0, g = 0;

  int lastNextV = start;
  int fromV, nextV;
  int nextFromV, lastPossibleNextV;

  double y_opt_length;
  double broken_edge_length;

  fromV = path[lastNextV];

  long initial_distance = path_cost();

  do {
    nextV = -1;

    broken_edge = make_sorted_pair(lastNextV, fromV);
    broken_edge_length = graph[broken_edge.first][broken_edge.second];

    if (joined_set.count(broken_edge) > 0) break;

    for (int possibleNextV = path[fromV]; nextV == -1 && possibleNextV != start; possibleNextV = path[possibleNextV]) {
      g_local = broken_edge_length - graph[fromV][possibleNextV];

      if (!(
        broken_set.count(make_sorted_pair(fromV, possibleNextV)) == 0 &&
        g + g_local > 0 &&
        path[possibleNextV] != 0 &&
        possibleNextV != path[fromV]
      )) {
        lastPossibleNextV = possibleNextV;
        continue;
      }

      nextV = possibleNextV;
    }

    if (nextV != -1) {
      broken_set.insert(broken_edge);
      joined_set.insert(make_sorted_pair(fromV, nextV));

      y_opt_length = graph[fromV][start];

      g_opt_local = g + (broken_edge_length - y_opt_length);

      if (g_opt_local > g_opt) {
        g_opt = g_opt_local;
        opt = path;
        opt[start] = fromV;
      }

      g += broken_edge_length - graph[fromV][nextV];
      reverse_segment(fromV, lastPossibleNextV);
      nextFromV = lastPossibleNextV;
      path[fromV] = nextV;

      lastNextV = nextV;
      fromV = nextFromV;
    }

  } while (nextV != -1);

  path = opt;
  long distanceAfter = path_cost();
  assert(distanceAfter <= initial_distance);
  cout << "# " << distanceAfter << " -vs- " << initial_distance << endl;
}


pair<int, int> LK_HEUR::make_sorted_pair (int x, int y) {
  return x < y ? make_pair(x, y) : make_pair(y, x);
}

void LK_HEUR::reverse_segment (int start, int end) {
  int current = start;
  int next = path[start];
  int nextNext;
  do {
    // look ahead to where we need to go after this iteration
    nextNext = path[next];

    // reverse the direction at this point
    path[next] = current;

    // move to the next pointer
    current = next;
    next = nextNext;
  } while (current != end);
}

double LK_HEUR::path_cost () {
  uint i;
  long cost = 0;

  for (i = 0; i < path.size(); i++)
    cost += graph[i][path[i]];

  // cout << "# " << cost << endl;
  return cost;
}
