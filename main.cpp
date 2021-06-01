#include "delta_star_plus_one.hpp"
#include "delta_star_plus_one_wtd.hpp"
#include <fstream>
#include <cmath>
#include <chrono>
#include "Kruskals.hpp"
#include "Prims.hpp"
constexpr double eps = 1e-7;

int main(int argc, char *argv[]) {
  // takes in file name through commandline
  std::fstream fin(argv[1], std::ios::in);
  std::map<int, std::set<int>> edges;
  std::map<int,std::map<int,double>> weighted_graph;
  std::map<std::pair<int, int>, double> weights;
  std::map<int,std::map<int,double>> weighted_edges;
  int N;
  fin >> N;
  int edg_cnt = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      double W;
      fin >> W;
      if (W > 0) {
        edg_cnt++;
        edges[i].insert(j);
        weights[std::make_pair(i,j)] = W;
        weighted_graph[i][j] = W;
      }
      // int present;
      // fin >> present;
      // if(present == 1)
      // {
      //   edges[i].insert(j);//adjacency list.
      //   edg_cnt++;
      // }
    }
  }
  fin.close();
  //printing the graph
  /* 
  for(int i = 0; i < N; i++) {
    cout << i << " : ";
    for(auto& v : edges[i]) {
      cout << v << ' ';
    } 
    cout << endl;
  }
  */
  auto start = std::chrono::high_resolution_clock::now();
  std::map<int,std::set<int>>* graph = delta_star_plus_one_wtd(edges,weights,3);
  auto stop = std::chrono::high_resolution_clock::now();
  auto bmst_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  start = std::chrono::high_resolution_clock::now();
  std::pair<double,std::map<int,std::map<int,double>>> k_g  = kruskals(weighted_graph);
  stop = std::chrono::high_resolution_clock::now();
  auto kruskal_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  start = std::chrono::high_resolution_clock::now();
  std::pair<double,std::map<int,std::map<int,double>>> p_g = prims(weighted_graph);
  stop = std::chrono::high_resolution_clock::now();
  auto prims_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  // auto start = std::chrono::high_resolution_clock::now();
  // std::map<int,std::set<int>> result = delta_star_plus_one(edges);
  // auto stop = std::chrono::high_resolution_clock::now();
  // auto bmst_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  int count = 0;
  double total_weight = 0.0;
  int max_degree = 0;
  std::pair<int,int> p;
  // for(auto i: result)
  // {
  //   max_degree = std::max(max_degree,(int)result[i.first].size());
  //   for(int j: i.second)
  //   {
  //     assert(edges[i.first].find(j) != edges[i.first].end());
  //     ++count;
  //   }
  // }
  
  for (auto i : *graph) {
    for (auto j : i.second) {
      //std::cerr << i.first << " " << j << std::endl;
      assert(edges[i.first].find(j) != edges[i.first].end());
      p.first = i.first;
      p.second = j;
      total_weight += weights[p];
      //assert(fabs(weighted_edges[i.first][j.first]-j.second) <= 1e-7);//verifies that the tree is valid.
      ++count;    
    }
    max_degree = std::max(max_degree, (int) i.second.size());
  }
  total_weight /= 2.0;
  //std::cerr<<"Kruskal time = "<<k_g.first<<" Prim time = "<<p_g.first<<'\n';
  assert(fabs(p_g.first-k_g.first) <= 1e-7);
  assert(count / 2 == N - 1);
  //std::cout<<bmst_time/1e9<<" "<<max_degree<<" "<<edg_cnt/2;
  std::cout<<bmst_time/1e9<<" "<<max_degree<<" "<<edg_cnt/2<<" "<<total_weight<<" "<<kruskal_time/1e9<<" "<<prims_time/1e9<<" "<<p_g.first;
  return 0;
}
