#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  int n = stoi(argv[1]);
  double p = stod(argv[2]);
  vector<vector<double>> g(n, vector<double>(n, 0));
  uniform_real_distribution<double> dis(0, 1);
  bernoulli_distribution dist(p);
  default_random_engine gen(
      std ::chrono ::system_clock ::now().time_since_epoch().count());
  double L = dis(gen), R = dis(gen);
  if (L > R) {
    swap(L, R);
  }
  uniform_real_distribution<double> distw(L, R);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double w = distw(gen);
      int yes = dist(gen);
      if (yes) {
        g[i][j] = g[j][i] = w;
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
    vector<vector<double>> _g(n, vector<double>(n, 0));
    if (_N % 2) {
      double _p = 6.0 / N;
      bernoulli_distribution _dist(p);
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          int ok = _dist(gen);
          double w = distw(gen);
          if (ok) {
            _g[i][j] = _g[j][i] = (g[i][j] == 0 ? w : 0);
          } else {
            _g[i][j] = _g[j][i] = g[i][j];
          }
        }
      }
    } else {
      normal_distribution<double> distp(0, 0.04);
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          if (g[i][j] > 0) {
            _g[i][j] = _g[j][i] = g[i][j] + distp(gen);
          }
        }
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