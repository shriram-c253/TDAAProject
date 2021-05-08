CXX = g++
CXXFLAGS = -g -std=c++17 -Wall
BIN = bmst

BIN : main.cpp delta_star_plus_one.cpp delta_star_plus_one_wtd.cpp Prims.cpp create_forest.cpp getst.cpp DisjointSetUnion.cpp
	$(CXX) $(CXXFLAGS) DisjointSetUnion.cpp getst.cpp create_forest.cpp Prims.cpp delta_star_plus_one_wtd.cpp delta_star_plus_one.cpp main.cpp -o $(BIN)

delta_star_plus_one.cpp : delta_star_plus_one.hpp 
	$(CXX) $(CXXFLAGS) delta_star_plus_one.hpp

delta_star_plus_one_wtd.cpp : delta_star_plus_one_wtd.hpp 
	$(CXX) $(CXXFLAGS) delta_star_plus_one_wtd.hpp

Prims.cpp: Prims.hpp
	$(CXX) $(CXXFLAGS) Prims.hpp

create_forest.cpp : create_forest.hpp
	$(CXX) $(CXXFLAGS) create_forest.hpp

getst.cpp : getst.hpp
	$(CXX) $(CXXFLAGS) getst.hpp

DisjointSetUnion.cpp : DisjointSetUnion.hpp
	$(CXX) $(CXXFLAGS) DisjointSetUnion.hpp

clean :	
	rm $(BIN)
