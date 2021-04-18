#include "delta_star_plus_one.hpp"

// finds the cycle formed after adding the edge (u, v) in the spanning tree, the vertices returned are in the cycle order (u, v1, v2, ... v)
std::vector<int> find_cycle(std::map<int, std::set<int>> spanning_tree, int u, int v) {
  std::vector<int> par((int) spanning_tree.size());
  // we will find a u, v path in the spanning tree (its unique) and we are done
  par[u] = -1;
  std::function<void(int)> dfs = [&](int from) {
    for(auto& to : spanning_tree[from]) {
      if(par[from] != to) {
        par[to] = from;
        dfs(to);
      }
    } 
  };
  dfs(u);
  std::vector<int> cycle;
  int member = v; 
  while(member != -1) {
    cycle.push_back(member);
    member = par[member];
  }
  return cycle;
}


// makes the vertex w non blocking
void make_non_blocking(int w, std::map<int, std::set<int>>& spanning_tree, int k, std::map<int, std::pair<int, int>>& cycle_pairs) {
  // base case
  if((int) spanning_tree[w].size() <= k - 2) {
    return;
  }
  auto [u, v] = cycle_pairs[w];
  make_non_blocking(u, spanning_tree, k, cycle_pairs);
  make_non_blocking(v, spanning_tree, k, cycle_pairs);

  assert((int) spanning_tree[u].size() <= k - 2 and (int) spanning_tree[v].size() <= k - 2);

  std::vector<int> cycle = find_cycle(spanning_tree, u, v);
  
  int w_prev = -1, w_next = -1;

  for(int i = 0; i < (int) cycle.size() - 1; i++) {
    if(cycle[i] == w) {
      assert(i != 0);
      w_prev = cycle[i - 1];
      w_next = cycle[i + 1];
    }
  }
  assert(w_prev != -1 and w_next != -1);
  
  // now u, and v have degree <= k - 2 and hence we can add the edge (u, v) and remove the edge from w to one of w_next, w_prev
  spanning_tree[u].insert(v);
  spanning_tree[v].insert(u);
  spanning_tree[w].erase(w_next);
  spanning_tree[w_next].erase(w);
}

/*
 * [Description] : takes as input a graph and returns a spanning tree whose maximum degree is atmost one more of the optimal minimum degree spanning tree
 */
std::map<int, std::set<int>> delta_star_plus_one(std::map<int, std::set<int>> graph) {
  
  // get a spanning tree for the graph
  std::map<int, std::set<int>> spanning_tree = get_spanning_tree(graph);
  int k = 0;
  for(auto& e : spanning_tree) {
    k = std::max(k, (int) e.second.size());
  } 

  while(true) {
    // get the forest and bad_vertices after removing removing vertices of degree >= k - 1 
    auto [bad_vertices, forest] = create_forest(spanning_tree, k);     
    std::set<int> good_vertices;
    // construct a dsu over the forest
    dsu d(graph.size()); 
    for(auto& e : forest) {
      int from = e.first;
      good_vertices.insert(from);
      for(auto& to : e.second) {
        d.Union(to, from);
        good_vertices.insert(to);
      }
    }

    int degree_k_vertex_count = (int) bad_vertices.first.size();
     
    std::map<int, std::pair<int, int>> cycle_pairs; // this stores for every degree k - 1 and degree k vertex, the pair of vertices (u, v)
                                          // where u-v was the edge on adding which the vertex became good

    for(auto& e : graph) {
      if((int) bad_vertices.first.size() < degree_k_vertex_count) {
        // we have already found degree k vertex which is good
        break;
      }
      int from = e.first;
      // the edges that we consider to add are only between 2 good vertices
      if(good_vertices.find(from) == good_vertices.end()) {
        break;
      }
      for(auto& to : e.second) {
        // the edges that we consider to add are only between 2 good vertices
        if(good_vertices.find(to) != good_vertices.end()) {
          break;
        }

        // now both from and to are good
        if(d.findParent(from) != d.findParent(to)) {
          // (from, to) forms an edge containing 2 components
          std::vector<int> cycle = find_cycle(spanning_tree, from, to);
          for(auto& vertex : cycle) {
            bad_vertices.first.erase(vertex);
            bad_vertices.second.erase(vertex);
            good_vertices.insert(vertex);
            if(cycle_pairs.find(vertex) == cycle_pairs.end()) {
              cycle_pairs[vertex] = {from, to};  // setting cycle pair for a vertex for which we have already found a cycle pair is wrong.
            }
          }
          // unite the forests lying on this cycle
          for(int i = 0; i < (int) cycle.size() - 1; i++) {
            d.Union(cycle[i], cycle[i + 1]);
          } 
          d.Union(to, from);
          break;
        }
      }
    }
    if((int) bad_vertices.first.size() == degree_k_vertex_count) {
      // we could not convert any degree k vertex that can be made good
      return spanning_tree;
    }
    
    int w = -1; // represents the vertex on which we want to apply the improvement 
    
    for(auto& vertex : good_vertices) {
      if((int) spanning_tree[vertex].size() == k) {
        w = vertex;
        break;
      }
    }
    assert(w != -1);
    
    make_non_blocking(w, spanning_tree, k, cycle_pairs);

    // update k for the next round
    k = 0;
    for(auto& e : spanning_tree) {
      k = std::max(k, (int) e.second.size());
    } 
  }
}
