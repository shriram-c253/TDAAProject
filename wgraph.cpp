#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  int n = stoi(argv[1]);
  double p = stod(argv[2]);
  vector<vector<double>> g(n, vector<double>(n, 0.0));
  uniform_real_distribution<double> dist(0, 1);
  bernoulli_distribution dis(p);
  default_random_engine gen(
      std ::chrono ::system_clock ::now().time_since_epoch().count());
  double L = dist(gen), R = dist(gen);
  if (L > R) {
    swap(L, R);
  }
  uniform_real_distribution<double> distw(L, R);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double w = distw(gen);
      int yes = dis(gen);
      if (yes) {
        g[i][j] = g[j][i] = w;
      }
    }
  }
  fstream fout(argv[3], ios::out);
  fout << n << "\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fout << g[i][j] << " \n"[j == n - 1];
    }
  }
  fout.close();
  return 0;
}