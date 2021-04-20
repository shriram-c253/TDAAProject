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
    bool operator()(std::pair<int,std::pair<int,int>> a, std::pair<int,std::pair<int,int>> b);
};
std::pair<int,std::map<int,std::map<int,int>>> prims(std::map<int,std::map<int,int>> graph,int d_bound,int src = 0);
#endif