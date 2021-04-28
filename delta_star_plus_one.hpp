#ifndef DELTA_STAR_PLUS_ONE
#define DELTA_STAR_PLUS_ONE
#include "DisjointSetUnion.hpp"
#include "getst.hpp"
#include "create_forest.hpp"
#include "assert.h"
#include <algorithm>
namespace bst {
  std::vector<int> find_cycle(std::map<int, std::set<int>> spanning_tree, int u, int v);
  void make_non_blocking(int w, std::map<int, std::set<int>>& spanning_tree, int k, std::map<int, std::pair<int, int>>& cycle_pairs);
}
std::map<int, std::set<int>> delta_star_plus_one(std::map<int, std::set<int>> graph);
#endif
