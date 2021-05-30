#ifndef PRIMS
#define PRIMS
#include<iostream>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<vector>
#include<cassert>
class comp
{
    public:
    bool operator()(std::pair<double,std::pair<int,int>> a, std::pair<double,std::pair<int,int>> b);
};
std::pair<double,std::map<int,std::map<int,double>>>* prims(std::map<int,std::map<int,double>> graph,int d_bound,int src = 0);
std::pair<double,std::map<int,std::map<int,double>>> prims(std::map<int,std::map<int,double>> graph);
#endif
