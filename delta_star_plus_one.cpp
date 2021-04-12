// finds the cycle formed after adding the edge (u, v) in the spanning tree, the vertices returned are in the cycle order (u, v1, v2, ... v)
std::vector<int> find_cycle(std::map<int, std::set<int>> spanning_tree, int u, int v) {
  std::vector<int> par((int) spanning_tree.size());
  // we will find a u, v path in the spanning tree (its unique) and we are done
  par[u] = -1;
  function<void(int)> dfs = [&](int from) {
    for(auto& to : spanning_tree[from]) {
      if(par[from] != to) {
        par[to] = from;
        dfs(to);
      }
    } 
  };
  vector<int> cycle;
  int member = v; 
  while(par[member] != -1) {
    cycle.push_back(member);
    member = par[member];
  }
  return cycle;
}

/*
 * [Description] : takes as input a graph and returns a spanning tree whose maximum degree is atmost one more of the optimal minimum degree spanning tree
 */
std::map<int, std::set<int>> delta_star_plus_one(std::map<int, std::set<int>> graph) {
  
  // get a spanning tree for the graph
  std::map<int, std::set<int>> spanning_tree = get_spanning_tree(graph);
  int k = 0;
  for(auto& e : spanning_tree) {
    k = std::max(k, e.second.size());
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
    
    int u, v; // these are the vertices to which an edge is added while joining 2 forests
    int w = -1; // represents the vertex on which we want to apply the improvement 
    
    vector<int> cycle; // represents the cycle we will find by joining (u, v)
    
    for(auto& e : graph) {
      if(bad_vertices.first.size() < degree_k_vertex_count) {
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
        if(good_vertices.find(to) != good.end()) {
          break;
        }

        // now both from and to are good
        if(d.findParent(from) != d.findParent(to)) {
          // (from, to) forms an edge containing 2 components
          auto cycle = find_cycle(spanning_tree, from, to);
          for(auto& vertex : cycle) {
            bad_vertices.first.erase(vertex);
            bad_vertices.second.erase(vertex);
            good_vertices.add(vertex);
          }
          // unite the forests lying on this cycle
          for(int i = 0; i < (int) cycle.size() - 1; i++) {
            d.Union(cycle[i], cycle[i + 1]);
          } 
          d.Union(to, from);
          u = to, v = from; // save to and from for later step
          break;
        }
      }
    }
    if(bad_vertices.first.size() == degree_k_vertex_count) {
      // we could not convert any degree k vertex that can be made good
      return spanning_tree;
    }
    
    for(auto& vertex : good_vertices) {
      if(spanning_tree[vertex].size() == k) {
        w = vertex;
        break;
      }
    }
    assert(w != -1);
    if(spanning_tree[u].size() < k - 2 and spanning_tree[v].size() < k - 2) {
      // then we can simply add the (u, v) and remove vertices adjacent to v from the spanning_tree
    }
    else {

    }
  }
}



