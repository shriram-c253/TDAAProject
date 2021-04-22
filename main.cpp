#include "delta_star_plus_one.hpp"
#include <fstream>

int main(int argc, char *argv[]) {
  // takes in file name through commandline
  std::fstream fin(argv[1], std::ios::in);
  std::map<int, std::set<int>> edges;
  std::map<std::pair<int, int>, int> weights;
  int N;
  fin >> N;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      int W;
      fin >> W;
      if (W) {
        edges[i].insert(j);
        edges[j].insert(i);
        weights[{i, j}] = weights[{j, i}] = W;
      }
    }
  }
  fin.close();
  std::map<int, std::set<int>> bMST = delta_star_plus_one(edges);
  std::fstream fout("result.txt", std::ios::out);
  int count = 0;
  for (auto i : bMST) {
    for (auto j : i.second) {
      std::cout << i.first << " " << j << std::endl;
      ++count;
    }
  }
  assert(count == N - 1);
  return 0;
}
