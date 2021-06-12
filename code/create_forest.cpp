#include "create_forest.hpp"

std::pair<std::pair<std::set<int>, std::set<int>>, std::map<int, std::set<int>>>
create_forest(std::map<int, std::set<int>> edges, int k) {
  // first member of the pair is the set of bad vertices of degree k, second
  // member is the k-1 set.
  /*
  for(auto& e : edges) {
    cout << e.first << " : " ;
    for(auto& v : e.second) {
      cout << v << ' ';
    }
    cout << endl;
  }
  */
  std::set<int> bad_vertices, sk, skminus;
  for (std::pair<int, std::set<int>> p : edges) {
    int degree_of_vertex = p.second.size();
    if ((degree_of_vertex == k) || (degree_of_vertex == k - 1)) {
      if (degree_of_vertex == k)
        sk.insert(p.first);
      else
        skminus.insert(p.first);
      bad_vertices.insert(p.first);
    }
  }
  for (int bad_vertex : bad_vertices)
    edges.erase(bad_vertex);
  for (auto &p : edges) {
    for (int bad_vertex : bad_vertices)
      p.second.erase(bad_vertex);
  }
  return std::make_pair(std::make_pair(sk, skminus), edges);
}
