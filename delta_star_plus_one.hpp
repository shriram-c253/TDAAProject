#ifndef DELTA_STAR_PLUS_ONE
#define DELTA_STAR_PLUS_ONE
#include "DisjointSetUnion.hpp"
#include "getst.hpp"
#include "create_forest.hpp"
std::vector<int> find_cycle(std::map<int, std::set<int>> spanning_tree, int u, int v);
std::map<int, std::set<int>> delta_start_plus_one(std::map<int, std::set<int>> graph);
#endif
