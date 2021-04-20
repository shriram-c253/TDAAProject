#include "Prims.hpp"

bool comp::operator()(std::pair<int,std::pair<int,int>> a, std::pair<int,std::pair<int,int>> b) 
{
    return a.first > b.first;
}

std::pair<int,std::map<int,std::map<int,int>>> prims(std::map<int,std::map<int,int>> graph,int d_bound,int src)
{
    std::priority_queue<std::pair<int,std::pair<int,int>>,std::vector<std::pair<int,std::pair<int,int>>>,comp> mpq;
    std::map<int,std::map<int,int>> sp_tree;

    for(std::pair<int,int> e:graph[src])
    {
        mpq.push({e.second,{src,e.first}});
    }

    int done=1;
    int n = graph.size();
    int totcost=0;

    while(done<n)
    {
        if(mpq.empty())
        {
            std::cout << "Invalid Degree Bound" << std::endl;
            assert(false);
        }
        std::pair<int,std::pair<int,int>> curr_v_d = mpq.top();
        mpq.pop();
        int w = curr_v_d.first,v = curr_v_d.second.second,u = curr_v_d.second.first;

        if(sp_tree[u].size() >= d_bound || sp_tree.find(v)!=sp_tree.end())
        continue;

        totcost += w;
        sp_tree[u][v] = w;
        sp_tree[v][u] = w;

        for(std::pair<int,int> e:graph[v])
        {
            int v1 = e.first;
            int w1 = e.second;

            if(sp_tree.find(v1)!=sp_tree.end()) continue;            
            mpq.push({w1,{v,v1}});

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