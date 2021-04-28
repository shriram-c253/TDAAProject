#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  int n = stoi(argv[1]);
  double p = stod(argv[2]);
  vector<vector<int>> g(n, vector<int>(n, 0));
  bernoulli_distribution dist(p);
  default_random_engine gen(
      std ::chrono ::system_clock ::now().time_since_epoch().count());
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int yes = dist(gen);
      if (yes) {
        g[i][j] = g[j][i] = 1;
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