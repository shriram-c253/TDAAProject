#include "DisjointSetUnion.hpp"

dsu::dsu() { n = 0; }

dsu::dsu(int n) {
  this->n = n;
  p.resize(n);
  rank = std::vector<int>(n, 0);

  for (int i = 0; i < n; i++) {
    p[i] = i;
  }
}

void dsu::add_one() {
  p.push_back(n++);
  rank.push_back(0);
}

int dsu::findParent(int i) {
  if (p[i] != i) {
    return p[i] = findParent(p[i]);
  }

  return i;
}

void dsu::link(int i, int j) {
  if (rank[i] > rank[j]) {
    p[j] = i;
  }

  else {
    p[i] = j;
    if (rank[i] == rank[j])
      rank[j]++;
  }
}

void dsu::Union(int i, int j) {
  i = findParent(i);
  j = findParent(j);

  if (i != j)
    link(i, j);
}

/*
int main()
  {
  int n;
  std::cin >> n;
  dsu d(n);
  int m;
  std::cin >> m;
  int a, b;
  for (int i = 0; i < m; i++) {
    std::cin >> a >> b;
    a--;
    b--;

    d.Union(a, b);
  }

  for (int i = 0; i < n; i++)
    std::cout << d.findParent(i) + 1 << ' ';

  std::cout << std::endl;
}
*/
