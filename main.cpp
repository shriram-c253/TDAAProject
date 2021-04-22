#include<iostream>
#include<cstdlib>
#include<vector> 
#include<algorithm>
#include<utility>
#include<cmath>
#include<map>
#include<random>
#include"Prims.hpp"

std::random_device rd{};    
std::mt19937 engine{rd()};
std::uniform_real_distribution<double> distri{0.0, 1.0};

double getnum()
{
    return distri(engine);
}

double dist(std::pair<double,double> a,std::pair<double,double> b)
{
    return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

std::vector<std::pair<double,double>> get_points(int n)
{
    std::vector<std::pair<double,double>> points;
    while(n--)
    points.push_back({getnum(),getnum()});
    return points;
}

std::map<int,std::map<int,double>> get_graph(std::vector<std::pair<double,double>> points)
{
    std::map<int,std::map<int,double>> graph;
    int n = points.size();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j) continue;
            graph[i][j] = dist(points[i],points[j]);
        }
    }
    return graph;
}

std::map<int,std::map<int,double>> create_graph(int n)
{
    return get_graph(get_points(n));
}

int main()
{
    int n;
    std::cin >> n;
    int d;
    std::cin >> d;
    std::map<int,std::map<int,double>> graph = create_graph(n);


    bool output_graph = false;


    if(output_graph)
    {
        std::cout << "ORIGINAL GRAPH" << std::endl;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==j) std::cout << 0 << ' ';
                else std::cout << graph[i][j] << ' ';
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    std::cout << "BOUNDED MST" << std::endl;

    std::pair<double,std::map<int,std::map<int,double>>> sp_tree_d = prims(graph,d);

    std::cout << sp_tree_d.first << std::endl;

    if(output_graph)
    {
        for(std::pair<int,std::map<int,double>> x:sp_tree_d.second)
        {
            for(std::pair<int,double> y:x.second)
            {
                if(x.first > y.first) continue;
                std::cout << x.first << ' ' << y.first << ' ' << y.second << std::endl;
            }
        }

        std::cout << std::endl;
    }
    

    std::cout << "ACTUAL MST" << std::endl;

    std::pair<double,std::map<int,std::map<int,double>>> sp_tree = prims(graph);

    std::cout << sp_tree.first << std::endl;

    if(output_graph)
    {
        for(std::pair<int,std::map<int,double>> x:sp_tree.second)
        {
            for(std::pair<int,double> y:x.second)
            {
                if(x.first > y.first) continue;
                std::cout << x.first << ' ' << y.first << ' ' << y.second << std::endl;
            }
        }
    }

    std::cout << (sp_tree.first == sp_tree_d.first) << std::endl;
}