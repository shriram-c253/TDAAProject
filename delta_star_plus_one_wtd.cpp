#include "delta_star_plus_one_wtd.hpp"

namespace bmst
{
    // finds the cycle formed after adding the edge (u, v) in the spanning tree, the
    // vertices returned are in the cycle order (u, v1, v2, ... v)
    std::vector<int> find_cycle(std::map<int, std::set<int>> spanning_tree, int u,
                                                            int v)
    {
        std::vector<int> par((int)spanning_tree.size());
        // we will find a u, v path in the spanning tree (its unique) and we are done
        par[u] = -1;
        std::function<void(int)> dfs = [&](int from)
        {
            for (auto &to : spanning_tree[from])
            {
                if (par[from] != to)
                {
                    par[to] = from;
                    dfs(to);
                }
            }
        };
        dfs(u);
        std::vector<int> cycle;
        int member = v;
        while (member != -1)
        {
            cycle.push_back(member);
            member = par[member];
        }
        return cycle;
    }

    // makes the vertex w non blocking
    void make_non_blocking(int w, std::map<int, std::set<int>> &spanning_tree, int k, std::map<int, std::pair<int, int>> &cycle_pairs, std::map<std::pair<int, int>, double> &weights)
    {
        // base case
        if ((int)spanning_tree[w].size() <= k - 2)
        {
            return;
        }
        auto [u, v] = cycle_pairs[w];
        make_non_blocking(u, spanning_tree, k, cycle_pairs, weights);
        make_non_blocking(v, spanning_tree, k, cycle_pairs, weights);

        assert((int)spanning_tree[u].size() <= k - 2 and (int) spanning_tree[v].size() <= k - 2);

        std::vector<int> cycle = find_cycle(spanning_tree, u, v);

        int w_prev = -1, w_next = -1;

        for (int i = 0; i < (int)cycle.size() - 1; i++)
        {
            if (cycle[i] == w)
            {
                assert(i != 0);
                w_prev = cycle[i - 1];
                w_next = cycle[i + 1];
            }
        }
        assert(w_prev != -1 and w_next != -1);

        // Heuristic 4 : (On lines with Heuristic 3)
        // now u, and v have degree <= k - 2 and hence we can add the edge (u, v) and
        // remove the edge from w to one of w_next, w_prev
        // remove that edge which has higher cost
        if (weights[{w, w_next}] < weights[{w, w_prev}])
        {
            std::swap(w_prev, w_next);
        }
        spanning_tree[u].insert(v);
        spanning_tree[v].insert(u);
        spanning_tree[w].erase(w_next);
        spanning_tree[w_next].erase(w);
    }
}

using namespace bmst;

/*
 * [Description] : takes as input a graph and returns a spanning tree whose
 * maximum degree is atmost one more of the optimal minimum degree spanning tree
 * and also tries to reduce the weight of the formed spanning tree to as much extent as possible
 */
std::map<int, std::set<int>>* delta_star_plus_one_wtd(std::map<int, std::set<int>> graph, std::map<std::pair<int, int>, double> &weights, int d_bound)
{

    // Heuristic 1 :
    // get a spanning tree for the graph by running a minimum weight spanning tree algorithm
    // This ensures that the spanning tree with which we start has the smallest weight possible
    // TODO : This is not done yet
    std::map<int, std::set<int>> spanning_tree = get_spanning_tree_wtd(graph, weights);
    int k = 0;
    for (auto &e : spanning_tree)
    {
        k = std::max(k, (int)e.second.size());
    }

    // We return the best graph stored in the history
    std::map<int, std::set<int>> best_st;
    int best_wt = 1e9;
    bool d_bound_reached = true;

    // sorted weights will store the weights and the corresponding vertices in increasing order of edge costs
    std::set<std::pair<double, std::pair<int, int>>> sorted_weights;
    for (auto w : weights)
    {
        sorted_weights.insert({w.second, w.first});
    }

    while (true)
    {
        if (k <= d_bound)
        {
            d_bound_reached = true;
        }

		if(d_bound_reached == true)
		{
			int tot_weight = 0;
			for(auto &adj: spanning_tree)
			{
				for(int vertex:adj.second)
				{
					tot_weight += weights[{adj.first,vertex}];
				}
			}

			if(tot_weight < best_wt)
			{
				best_wt = tot_weight;
				best_st = spanning_tree;
			}
		}
        // get the forest and bad_vertices after removing removing vertices of
        // degree >= k - 1
        auto [bad_vertices, forest] = create_forest(spanning_tree, k);
        std::set<int> good_vertices;
        // construct a dsu over the forest
        dsu d(graph.size());
        for (auto &e : forest)
        {
            int from = e.first;
            good_vertices.insert(from);
            for (auto &to : e.second)
            { 
                d.Union(to, from);
                good_vertices.insert(to);
            }
        }

        int degree_k_vertex_count = (int)bad_vertices.first.size();

        //cout << degree_k_vertex_count << endl;

        std::map<int, std::pair<int, int>> cycle_pairs; // this stores for every degree k - 1 and degree k vertex,
                                                                                                        // the pair of vertices (u, v) where u-v was the edge on
                                                                                                        // adding which the vertex became good

        std::map<int, double> benefit; // this stores for every degree k vertex that is made good, the cost of the
                                                                     // maximum weight edge incident to it in the cycle we form adding an edge to
                                                                     // the spanning tree

        // Heuristic 2 :
        // our objective is to find the minimum weight edge that joins 2 forests, so that cost of the new
        // spanning tree on adding this edge is the smallest possible
        for (auto &e : sorted_weights)
        {
            if ((int)bad_vertices.first.size() < degree_k_vertex_count)
            {
                // we have already found degree k vertex which is good
                break;
            }
            int from = e.second.first;
            // the edges that we consider to add are only between 2 good vertices
            if (good_vertices.find(from) == good_vertices.end())
            {
                continue;
            }
            int to = e.second.second;
            // the edges that we consider to add are only between 2 good vertices
            if (good_vertices.find(to) == good_vertices.end())
            {
                continue;
            }
            // now both from and to are good
            if (d.findParent(from) != d.findParent(to))
            {
                // (from, to) forms an edge containing 2 components
                std::vector<int> cycle = find_cycle(spanning_tree, from, to);
                for (auto &vertex : cycle)
                {
                    bad_vertices.first.erase(vertex);
                    bad_vertices.second.erase(vertex);
                    good_vertices.insert(vertex);
                    if (cycle_pairs.find(vertex) == cycle_pairs.end())
                    {
                        cycle_pairs[vertex] = {from, to}; // setting cycle pair for a vertex for which we
                                                                                            // have already found a cycle pair is wrong.
                    }
                }
                // unite the forests lying on this cycle
                for (int i = 0; i < (int)cycle.size() - 1; i++)
                {
                    d.Union(cycle[i], cycle[i + 1]);
                }
                d.Union(to, from);

                // compute benefits
                for (int i = 0; i < (int)cycle.size() - 1; i++)
                {
                    int vertex = cycle[i];
                    // if its a degree k vertex
                    if ((int)spanning_tree[vertex].size() == k)
                    {
                        assert(i != 0);
                        int prev = cycle[i - 1];
                        int next = cycle[i + 1];
                        benefit[cycle[i]] = std::max(weights[{vertex, prev}], weights[{vertex, next}]);
                    }
                }
            }
        }

        if ((int)bad_vertices.first.size() == degree_k_vertex_count)
        {
            // we could not convert any degree k vertex that can be made good
            if(k<=d_bound)
            {
                return new std::map<int, std::set<int>>(best_st);
            }

			else
			{
				return NULL;
			}
        }

        // Heuristic 3 :
        int w = -1; // represents the vertex on which we want to apply the improvement
                                // and we choose the vertex that gives us the maximum benefit
        double max_benefit = 0;

        for (auto &vertex : good_vertices)
        {
            if ((int)spanning_tree[vertex].size() == k)
            {
                if (benefit[vertex] >= max_benefit)
                {
                    w = vertex;
                    max_benefit = benefit[vertex];
                }
            }
        }
        assert(w != -1);

        make_non_blocking(w, spanning_tree, k, cycle_pairs, weights);

        // update k for the next round
        k = 0;
        for (auto &e : spanning_tree)
        {
            k = std::max(k, (int)e.second.size());
        }
    }
}
