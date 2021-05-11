#ifndef KRUSKAL
#define KRUSKAL
#include "DisjointSetUnion.hpp"
#include<iostream>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<vector>
#include<cassert>
#include<algorithm>
std::pair<double,std::map<int,std::map<int,double>>>* bdd_kruskals(std::map<int,std::map<int,double>> graph,int d_bound);
std::pair<double,std::map<int,std::map<int,double>>> kruskals(std::map<int,std::map<int,double>> graph);
#endif