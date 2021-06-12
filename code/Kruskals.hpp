#ifndef KRUSKAL
#define KRUSKAL
#include "DisjointSetUnion.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>
std::pair<double, std::map<int, std::map<int, double>>> *
bdd_kruskals(std::map<int, std::map<int, double>> graph, int d_bound);
std::pair<double, std::map<int, std::map<int, double>>>
kruskals(std::map<int, std::map<int, double>> graph);
#endif