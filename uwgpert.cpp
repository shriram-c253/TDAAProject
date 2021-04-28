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
  string name = "orig_" + string(argv[3]);
  fstream fout(name.c_str(), ios::out);
  fout << n << "\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fout << g[i][j] << " \n"[j == n - 1];
    }
  }
  fout.close();
  int N = stoi(argv[4]);
  for (int _N = 0; _N < N; ++_N) {
    double _p = 6.0 / N;
    bernoulli_distribution _dist(p);
    vector<vector<int>> _g(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int ok = _dist(gen);
        if (ok) {
          _g[i][j] = _g[j][i] = 1;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        _g[i][j] ^= g[i][j];
      }
    }
    string ne = "pert" + to_string(_N) + "_" + string(argv[3]);
    fstream fout(ne.c_str(), ios::out);
    fout << n << "\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        fout << _g[i][j] << " \n"[j == n - 1];
      }
    }
    fout.close();
  }
  return 0;
}