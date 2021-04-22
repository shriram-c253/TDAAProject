#include "Prims.hpp"

bool comp::operator()(std::pair<double,std::pair<int,int>> a, std::pair<double,std::pair<int,int>> b) 
{
    return a.first > b.first;
}

std::pair<double,std::map<int,std::map<int,double>>> prims(std::map<int,std::map<int,double>> graph,int d_bound,int src)
{
    std::priority_queue<std::pair<double,std::pair<int,int>>,std::vector<std::pair<double,std::pair<int,int>>>,comp> mpq;
    std::map<int,std::map<int,double>> sp_tree;

    for(std::pair<int,double> e:graph[src])
    {
        mpq.push({e.second,{src,e.first}});
    }

    int done=1;
    int n = graph.size();
    double totcost=0;

    while(done<n)
    {
        if(mpq.empty())
        {
            std::cout << "Invalid Degree Bound" << std::endl;
            assert(false);
        }
        std::pair<double,std::pair<int,int>> curr_v_d = mpq.top();
        mpq.pop();
        double w = curr_v_d.first,v = curr_v_d.second.second,u = curr_v_d.second.first;

        if(sp_tree[u].size() >= d_bound || sp_tree.find(v)!=sp_tree.end())
        continue;

        totcost += w;
        sp_tree[u][v] = w;
        sp_tree[v][u] = w;

        for(std::pair<int,double> e:graph[v])
        {
            int v1 = e.first;
            double w1 = e.second;

            if(sp_tree.find(v1)!=sp_tree.end()) continue;            
            mpq.push({w1,{v,v1}});

        }
        done++;
    }

    return{totcost,sp_tree};
}

std::pair<double,std::map<int,std::map<int,double>>> prims(std::map<int,std::map<int,double>> graph)
{
    std::priority_queue<std::pair<double,std::pair<int,int>>,std::vector<std::pair<double,std::pair<int,int>>>,comp> mpq;
    std::map<int,std::map<int,double>> sp_tree;
    int src = 0;
    for(std::pair<int,double> e:graph[src])
    {
        mpq.push({e.second,{src,e.first}});
    }

    int done=1;
    int n = graph.size();
    double totcost=0;

    while(done<n)
    {
        if(mpq.empty())
        {
            std::cout << "Invalid Degree Bound" << std::endl;
            assert(false);
        }
        std::pair<double,std::pair<int,int>> curr_v_d = mpq.top();
        mpq.pop();
        double w = curr_v_d.first,v = curr_v_d.second.second,u = curr_v_d.second.first;

        if(sp_tree.find(v)!=sp_tree.end())
        continue;

        totcost += w;
        sp_tree[u][v] = w;
        sp_tree[v][u] = w;

        for(std::pair<int,double> e:graph[v])
        {
            int v1 = e.first;
            double w1 = e.second;

            if(sp_tree.find(v1)!=sp_tree.end()) continue;            
            mpq.push({w1,{v,v1}});

        }
        done++;
    }

    return{totcost,sp_tree};
}