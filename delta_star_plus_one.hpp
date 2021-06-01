#ifndef DELTA_STAR_PLUS_ONE_WTD
#define DELTA_STAR_PLUS_ONE_WTD
#include "DisjointSetUnion.hpp"
#include "assert.h"
#include "create_forest.hpp"
#include "getst.hpp"
#include <algorithm>
namespace bmst {
std::vector<int> find_cycle(std::map<int, std::set<int>> spanning_tree, int u,
                            int v);
void make_non_blocking(int w, std::map<int, std::set<int>> &spanning_tree,
                       int k, std::map<int, std::pair<int, int>> &cycle_pairs,
                       std::map<std::pair<int, int>, double> &weights);
} // namespace bmst
std::map<int, std::set<int>> *
delta_star_plus_one_wtd(std::map<int, std::set<int>> graph,
                        std::map<std::pair<int, int>, double> &weights,
                        int d_bound);
#endif
