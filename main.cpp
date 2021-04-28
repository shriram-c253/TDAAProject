#include "delta_star_plus_one.hpp"
#include "delta_star_plus_one_wtd.hpp"
#include <fstream>

constexpr double eps = 1e-7;

int main(int argc, char *argv[]) {
  // takes in file name through commandline
  std::fstream fin(argv[1], std::ios::in);
  std::map<int, std::set<int>> edges;
  std::map<std::pair<int, int>, double> weights;
  int N;
  fin >> N;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      double W;
      fin >> W;
      if (W > eps) {
        edges[i].insert(j);
        edges[j].insert(i);
        weights[{j, i}] = W;
        weights[{i, j}] = W;
      }
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
  std::map<int, std::set<int>> bMST = delta_star_plus_one_wtd(edges, weights);
  std::fstream fout("result.txt", std::ios::out);
  int count = 0;
  int max_degree = 0;
  for (auto i : bMST) {
    for (auto j : i.second) {
      //std::cout << i.first << " " << j << std::endl;
      assert(edges[i.first].find(j) != edges[i.first].end());
      ++count;    
    }
    max_degree = std::max(max_degree, (int) i.second.size());
  }
  std::cout << "Maximum Degree " << max_degree << std::endl;
  assert(count / 2 == N - 1);
  return 0;
}
