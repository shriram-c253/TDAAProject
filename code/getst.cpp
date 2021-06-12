#include "getst.hpp"

// Returns a spanning tree by DFS
std::map<int, std::set<int>>
get_spanning_tree(std::map<int, std::set<int>> &edges) {
  int n = (int)edges.size();
  std::vector<bool> vis(n, 0);
  std::map<int, std::set<int>> spanning_tree;

  std::function<void(int)> dfs = [&](int u) {
    vis[u] = true;
    for (int v : edges[u]) {
      if (!vis[v]) {
        spanning_tree[u].insert(v);
        spanning_tree[v].insert(u);
        dfs(v);
      }
    }
  };
  dfs(0);
  return spanning_tree;
}

std::map<int, std::map<int, double>>
get_wtd_graph(std::map<int, std::set<int>> &graph,
              std::map<std::pair<int, int>, double> &weights) {
  std::map<int, std::map<int, double>> wtd_graph;
  for (auto &adj : graph) {
    for (int vertex : adj.second) {
      wtd_graph[adj.first][vertex] = weights[{adj.first, vertex}];
    }
  }
  return wtd_graph;
}

// Returns a MST by Kruskal's algorithm for the starting for of delta*+1
// algorithm
std::map<int, std::set<int>>
get_spanning_tree_wtd(std::map<int, std::set<int>> &graph,
                      std::map<std::pair<int, int>, double> &weights) {
  std::map<int, std::map<int, double>> wtd_std =
      kruskals(get_wtd_graph(graph, weights)).second;
  std::map<int, std::set<int>> new_edges;
  for (auto &edges : wtd_std) {
    if (new_edges.find(edges.first) == new_edges.end()) {
      new_edges[edges.first] = {};
    }
    for (auto &edge : edges.second) {
      new_edges[edges.first].insert(edge.first);
    }
  }
  return new_edges;
}
