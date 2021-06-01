#ifndef GETST
#define GETST
#include "Kruskals.hpp"
#include <functional>
#include <map>
#include <set>
#include <vector>
std::map<int, std::set<int>>
get_spanning_tree(std::map<int, std::set<int>> &graph);
std::map<int, std::set<int>>
get_spanning_tree_wtd(std::map<int, std::set<int>> &graph,
                      std::map<std::pair<int, int>, double> &weights);
#endif
