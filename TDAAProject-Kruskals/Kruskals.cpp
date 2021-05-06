#include "Kruskals.hpp"

std::pair<double,std::map<int,std::map<int,double>>> bdd_kruskals(std::map<int,std::map<int,double>> graph,int d_bound)
{
    std::vector<std::pair<double,std::pair<int,int>>> edges;
    for(std::pair<int,std::map<int,double>> x:graph)
    {
        for(std::pair<int,double> y:x.second)
        {
            if(x.first>y.first)
            edges.push_back({y.second,{x.first,y.first}});
        }
    }
    std::sort(edges.begin(),edges.end(),
        [&](std::pair<double,std::pair<int,int>> a, std::pair<double,std::pair<int,int>> b) {return a.first < b.first;}
    );
    
    std::map<int,std::map<int,double>> sp_tree;
    int n = graph.size();

    dsu d(n);
    int comps = n;
    double totcost = 0;

    for(std::pair<double,std::pair<int,int>> edge:edges)
    {
        double w = edge.first,u=edge.second.first,v=edge.second.second;
        if(sp_tree[u].size()>=d_bound || sp_tree[v].size()>=d_bound) continue;
        
        if(d.findParent(u)==d.findParent(v)) continue;
        totcost+=w;

        d.Union(u,v);
        comps--;

        sp_tree[u][v]=w;
        sp_tree[v][u]=w;
    }

    if(comps!=1)
    return {-1,sp_tree};

    return {totcost,sp_tree};
}


std::pair<double,std::map<int,std::map<int,double>>> kruskals(std::map<int,std::map<int,double>> graph)
{
    std::vector<std::pair<double,std::pair<int,int>>> edges;
    for(std::pair<int,std::map<int,double>> x:graph)
    {
        for(std::pair<int,double> y:x.second)
        {
            if(x.first>y.first)
            edges.push_back({y.second,{x.first,y.first}});
        }
    }
    std::sort(edges.begin(),edges.end(),
        [&](std::pair<double,std::pair<int,int>> a, std::pair<double,std::pair<int,int>> b) {return a.first < b.first;}
    );
    
    std::map<int,std::map<int,double>> sp_tree;
    int n = graph.size();

    dsu d(n);
    double totcost = 0;

    for(std::pair<double,std::pair<int,int>> edge:edges)
    {
        double w = edge.first,u=edge.second.first,v=edge.second.second;
        // if(sp_tree[u].size()>=d_bound || sp_tree[v].size()>=d_bound) continue;
        
        if(d.findParent(u)==d.findParent(v)) continue;
        totcost+=w;

        d.Union(u,v);

        sp_tree[u][v]=w;
        sp_tree[v][u]=w;
    }

    return {totcost,sp_tree};
}
