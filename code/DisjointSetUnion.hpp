#ifndef DSU
#define DSU
#include <iostream>
#include <vector>
class dsu {
  int n;
  std::vector<int> p;
  std::vector<int> rank;

public:
  dsu();
  dsu(int);
  void add_one();
  int findParent(int);
  void Union(int, int);

private:
  void link(int i, int j);
};
#endif
