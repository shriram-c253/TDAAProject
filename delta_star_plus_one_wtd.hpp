#ifndef DELTA_STAR_PLUS_ONE_WTD
#define DELTA_STAR_PLUS_ONE_WTD
#include "DisjointSetUnion.hpp"
#include "getst.hpp"
#include "create_forest.hpp"
#include "assert.h"
#include <algorithm>
namespace bmst {
  std::vector<int> find_cycle(std::map<int, std::set<int>> spanning_tree, int u, int v);
  int make_non_blocking(int w, std::map<int, std::set<int>>& spanning_tree, int k, std::map<int, std::pair<int, int>>& cycle_pairs, std::map<std::pair<int, int>, double>& weights);
}
std::map<int, std::set<int>>* delta_star_plus_one_wtd(std::map<int, std::set<int>> graph, std::map<std::pair<int, int>, double>& weights);
#endif
