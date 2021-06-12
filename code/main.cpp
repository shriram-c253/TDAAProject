#include "Kruskals.hpp"
#include "Prims.hpp"
#include "delta_star_plus_one.hpp"
#include "delta_star_plus_one_wtd.hpp"
#include <chrono>
#include <cmath>
#include <fstream>
constexpr double eps = 1e-7;

int main(int argc, char *argv[]) {
  // takes in file name through commandline
  std::fstream fin(argv[1], std::ios::in);
  std::map<int, std::set<int>> edges;
  std::map<int, std::map<int, double>> weighted_graph;
  std::map<std::pair<int, int>, double> weights;
  std::map<int, std::map<int, double>> weighted_edges;
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
        weights[std::make_pair(i, j)] = W;
        weighted_graph[i][j] = W;
      }
    }
  }
  fin.close();

  auto start = std::chrono::high_resolution_clock::now();
  std::map<int, std::set<int>> *graph3 =
      delta_star_plus_one_wtd(edges, weights, 3);
  auto stop = std::chrono::high_resolution_clock::now();
  auto bmst3_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
          .count();

  start = std::chrono::high_resolution_clock::now();
  std::map<int, std::set<int>> *graph4 =
      delta_star_plus_one_wtd(edges, weights, 4);
  stop = std::chrono::high_resolution_clock::now();
  auto bmst4_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
          .count();

  start = std::chrono::high_resolution_clock::now();
  std::pair<double, std::map<int, std::map<int, double>>> *bddk_g =
      bdd_kruskals(weighted_graph, 4);
  stop = std::chrono::high_resolution_clock::now();
  auto bdd_kruskal_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
          .count();

  start = std::chrono::high_resolution_clock::now();
  std::pair<double, std::map<int, std::map<int, double>>> *bddp_g =
      bdd_prims(weighted_graph, 4);
  stop = std::chrono::high_resolution_clock::now();
  auto bdd_prims_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
          .count();

  std::pair<double, std::map<int, std::map<int, double>>> mst =
      kruskals(weighted_graph);

  double total_weight3 = 0.0;
  int max_degree3 = 0;
  std::pair<int, int> p;

  for (auto i : *graph3) {
    for (auto j : i.second) {
      assert(edges[i.first].find(j) != edges[i.first].end());
      p.first = i.first;
      p.second = j;
      total_weight3 += weights[p];
    }
    max_degree3 = std::max(max_degree3, (int)i.second.size());
    assert(max_degree3 <= 3);
  }
  total_weight3 /= 2.0;

  double total_weight4 = 0.0;
  int max_degree4 = 0;

  for (auto i : *graph4) {
    for (auto j : i.second) {
      assert(edges[i.first].find(j) != edges[i.first].end());
      p.first = i.first;
      p.second = j;
      total_weight4 += weights[p];
    }
    max_degree4 = std::max(max_degree4, (int)i.second.size());
    assert(max_degree4 <= 4);
  }
  total_weight4 /= 2.0;

  if (bddk_g == NULL) {
    std::cerr << "KRUSKAL'S ERROR" << std::endl;
  }

  if (bddp_g == NULL) {
    std::cerr << "PRIMS'S ERROR" << std::endl;
  }
  assert(bddk_g != NULL);
  assert(bddp_g != NULL);

  std::cout << bmst3_time / 1e9 << " " << total_weight3 << " "
            << bmst4_time / 1e9 << " " << total_weight4 << " " << edg_cnt / 2
            << " " << bdd_kruskal_time / 1e9 << " " << bddk_g->first << " "
            << bdd_prims_time / 1e9 << " " << bddp_g->first << " " << mst.first;
  return 0;
}