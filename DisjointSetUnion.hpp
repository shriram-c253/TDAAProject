#ifndef DSU
#define DSU

#include <iostream>
#include <vector>
using namespace std;
class dsu {
  int n;
  vector<int> p;
  vector<int> rank;

public:
  dsu() { n = 0; }

  dsu(int n) {
    this->n = n;
    p.resize(n);
    rank = vector<int>(n, 0);

    for (int i = 0; i < n; i++) {
      p[i] = i;
    }
  }

  void add_one() {
    p.push_back(n++);
    rank.push_back(0);
  }

  int findParent(int i) {
    if (p[i] != i) {
      return p[i] = findParent(p[i]);
    }

    return i;
  }

private:
  void link(int i, int j) {
    if (rank[i] > rank[j]) {
      p[j] = i;
    }

    else {
      p[i] = j;
      if (rank[i] == rank[j])
        rank[j]++;
    }
  }

public:
  void Union(int i, int j) {
    i = findParent(i);
    j = findParent(j);

    if (i != j)
      link(i, j);
  }
};

int main() {
  int n;
  cin >> n;

  dsu d(n);

  int m;
  cin >> m;

  int a, b;

  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    a--;
    b--;

    d.Union(a, b);
  }

  for (int i = 0; i < n; i++)
    cout << d.findParent(i) + 1 << ' ';

  cout << endl;
}

#endif