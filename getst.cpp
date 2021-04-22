#include "getst.hpp"

std::map<int, std::set<int>>
get_spanning_tree(std::map<int, std::set<int>> edges) {
  int n = (int)edges.size();
  std::vector<bool> vis(n, 0);
  std::map<int, std::set<int>> spanning_tree;

  std::function<void(int)> dfs = [&](int u) {
    for (int v : edges[u]) {
      if (!vis[v]) {
        spanning_tree[u].insert(v);
        dfs(v);
      }
    }
  };
  dfs(0);
  return spanning_tree;
}
