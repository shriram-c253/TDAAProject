#ifndef KRUSKAL
#define KRUSKAL
#include "DisjointSetUnion.hpp"
#include "DisjointSetUnion.cpp"
#include<iostream>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<vector>
#include<cassert>
#include<algorithm>
std::pair<int,std::map<int,std::map<int,int>>> kruskals(std::map<int,std::map<int,int>> graph,int d_bound);
#endif