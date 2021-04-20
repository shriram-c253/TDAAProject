#include "Prims.hpp"

bool comp::operator()(std::pair<std::pair<int,int>,int> a,std::pair<std::pair<int,int>,int>  b)
{
    if(a.first.first != b.first.first)
    return a.first.first > b.first.first;

    return a.first.second > b.first.second;
}

std::pair<int,std::map<int,std::map<int,int>>> prims(std::map<int,std::map<int,int>> graph,int d_bound,int src)
{
    mapped_priority_queue<int,std::pair<int,int>,comp> mpq;
    std::map<int,std::map<int,int>> sp_tree;

    for(std::pair<int,int> e:graph[src])
    {
        mpq.push(e.first,{e.second,src});
    }

    int done=1;
    int n = graph.size();
    int totcost=0;

    while(done<n)
    {
        std::pair<int,std::pair<int,int>> curr_v_d = mpq.top();
        mpq.pop();
        int v = curr_v_d.first,u = curr_v_d.second.second,w = curr_v_d.second.first;
        if(sp_tree[u].size() >= d_bound) continue;
        if(sp_tree.find(v)!=sp_tree.end()) continue;

        totcost += w;
        sp_tree[u][v] = w;
        sp_tree[v][u] = w;

        mpq.erase(v);

        for(std::pair<int,int> e:graph[v])
        {
            int v1 = e.first;
            int w1 = e.second;

            if(sp_tree.find(v1)!=sp_tree.end()) continue;
            
            if(!mpq.present(v1))
            mpq.push(v1,{w1,v});

            else if(w1<mpq[v1].first)
            mpq.update(v1,{w1,v});
        }
        done++;
    }

    return{totcost,sp_tree};
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

    auto x = prims(g,db);
    std::cout << x.first << std::endl;

    for(auto k:x.second)
    {
        for(auto k1:k.second)
        std::cout << k.first << ' ' << k1.first << ' ' << k1.second << std::endl;
    }
}