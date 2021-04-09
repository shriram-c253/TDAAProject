std::map<int,std::set<int>> create_forest(std::map<int,std::set<int>> edges, int k)
{
	std::set<int> bad_vertices;
	for(std::pair<int,std::set<int>> p: edges)
	{
		int degree_of_vertex =  p.second.size();
		if((p == k) || (p == k-1))
			bad_vertices.add(p.first);
	}
	for(int bad_vertex: bad_vertices)
		edges.erase(bad_vertex);
	for(std::pair<int,std::set<int>> &p: edges)
	{
		for(int bad_vertex: bad_vertices)
			p.erase(bad_vertex);
	}
	return edges;
}
