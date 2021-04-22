#include "getst.hpp"

std::map<int, std::set<int>>
get_spanning_tree(std::map<int, std::set<int>> edges) {
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
  //cout << spanning_tree.size() << endl;
  return spanning_tree;
}
