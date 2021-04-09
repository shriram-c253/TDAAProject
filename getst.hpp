#ifndef GETST
#define GETST

#include <map>
#include <set>
#include <vector>

map<set<int>> get_spanning_tree(map<set<int>> edges) {
  int n = (int)m.size();
  vector<bool> vis(n, 0);
  map<set<int>> spanning_tree;

  function<void(int)> dfs = [&](int u) {
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

#endif