#include "Kruskals.hpp"

std::pair<int,std::map<int,std::map<int,int>>> kruskals(std::map<int,std::map<int,int>> graph,int d_bound)
{
    std::vector<std::pair<int,std::pair<int,int>>> edges;
    for(std::pair<int,std::map<int,int>> x:graph)
    {
        for(std::pair<int,int> y:x.second)
        {
            if(x.first>y.first)
            edges.push_back({y.second,{x.first,y.first}});
        }
    }
    std::sort(edges.begin(),edges.end(),
        [&](std::pair<int,std::pair<int,int>> a, std::pair<int,std::pair<int,int>> b) {return a.first < b.first;}
    );
    
    std::map<int,std::map<int,int>> sp_tree;
    int n = graph.size();

    dsu d(n);
    int done = 0;
    int totcost = 0;

    for(std::pair<int,std::pair<int,int>> edge:edges)
    {
        int w = edge.first,u=edge.second.first,v=edge.second.second;
        if(sp_tree[u].size()>=d_bound || sp_tree[v].size()>=d_bound) continue;
        
        if(d.findParent(u)==d.findParent(v)) continue;
        totcost+=w;

        d.Union(u,v);

        sp_tree[u][v]=w;
        sp_tree[v][u]=w;
    }

    return {totcost,sp_tree};
}

int main()
{
    int db;
    std::map<int,std::map<int,int>> g;

    int n,m;
    std::cin >> n >> m;

    int a,b,w;

    while(m--)
    {
        std::cin >> a >> b >> w;
        g[a][b]=w;
        g[b][a]=w;
    }
    std::cin >> db;

    auto x = kruskals(g,db);
    std::cout << x.first << std::endl;

    for(auto k:x.second)
    {
        for(auto k1:k.second)
        std::cout << k.first << ' ' << k1.first << ' ' << k1.second << std::endl;
    }
}