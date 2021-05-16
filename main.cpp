#include "delta_star_plus_one.hpp"
#include "delta_star_plus_one_wtd.hpp"
#include <fstream>
#include <cmath>
#include "Kruskals.hpp"
#include "Prims.hpp"
constexpr double eps = 1e-7;

int main(int argc, char *argv[]) {
  // takes in file name through commandline
  std::fstream fin(argv[1], std::ios::in);
  std::map<int, std::set<int>> edges;
  std::map<std::pair<int, int>, double> weights;
  //std::map<int,std::map<int,double>> weighted_edges;
  int N;
  fin >> N;
  int edg_cnt = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      double W;
      fin >> W;
      if (W > eps) {
        edg_cnt++;
        edges[i].insert(j);
        weights[std::make_pair(i,j)] = W;
      }
      /*
      int present;
      fin >> present;
      if(present == 1)
      {
        edges[i].insert(j);//adjacency list.
      }*/
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
  std::map<int,std::set<int>> graph = delta_star_plus_one_wtd(edges,weights);
  //std::pair<double,std::map<int, std::map<int,double>>>* kruskal_MST = 
  //std::fstream fout("result.txt", std::ios::out);
  // if(kruskal_MST == NULL)
  // {
  //   std::cout<<"-1";//invalid tree 
  //   return 0;
  // }
  int count = 0;
  int max_degree = 0;
  for (auto i : graph) {
    for (auto j : i.second) {
      //std::cout << i.first << " " << j << std::endl;
      assert(edges[i.first].find(j) != edges[i.first].end());
      //assert(fabs(weighted_edges[i.first][j.first]-j.second) <= 1e-7);//verifies that the tree is valid.
      ++count;    
    }
    max_degree = std::max(max_degree, (int) i.second.size());
  }
  std::cout<<max_degree<<" "<<edg_cnt/2;
  assert(count / 2 == N - 1);
  return 0;
}
