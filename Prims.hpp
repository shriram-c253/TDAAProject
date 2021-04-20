#ifndef PRIMS
#define PRIMS
#include<iostream>
#include<map>
#include<set>
#include<utility>
#include"PriorityQueueUpdate.hpp"
#include "PriorityQueueUpdate.cpp"
#define INF 1e18
class comp
{
    public:
    bool operator()(std::pair<std::pair<int,int>,int> a,std::pair<std::pair<int,int>,int>  b);
};
std::pair<int,std::map<int,std::map<int,int>>> prims(std::map<int,std::map<int,int>> graph,int d_bound,int src = 0);
#endif