# TDAAProject
This repository contains implementation of various heuristics for the Bounded Degree Minimum Spanning Tree (bMST) problem, which is to find a spanning tree of a given graph with minimum weight such that the maximum degree of any vertex of the output tree is less than a given value b, as a part of our project for the CS6100: Topics in Design and Analysis of Algorithms, Spring 2021 course. This project was implemented by Arjun Bharat (CS17B006), C Shriram (CS18B007), Pragyan Chakraborty (CS18B038) and Sarthak Kapoor (CS18B066).

As a part of this project, we have implemented a greedy modification of an [additional degree 1 approximation algorithm](https://drive.google.com/drive/u/1/folders/1NMQ4ei-7zAPwo7sph7Xp1hZhsFxP0jU5) to produce a bMST. We have also modified Kruskal's and Prim's standard algorithm by adding heuristcs for bMST.

## Directory Structure

- The **code** folder contains all the header files, corresponding implementations and test script used to run the three heuristics.
  - Modification of additional degree 1 algorithm
    - `create_forest` - Used to remove vertices of degree `k` and `k-1` from the current spanning tree `T` (where `k` is the maximum degree in `T`) creating a forest which is required by the algorithm.
    - `DisjointSetUnion` - Used the implement the `Disjoint Set Union` / `Union Find` algorithm
    - `getst` - Used to return an initial spanning tree for the algorithm as a starting point. The weighted version of the algorithm call simple `Kruskal's` algorithm through this.
    - `delta_star_plus_one` - Implementation of the original version of additional degree one approximation algorithm (for unweighted graphs).
    - `delta_star_plus_one_wtd` - Implementation of the modified version of additional degree one approximation algorithm (for unweighted graphs). It takes in an additional paramater `d_bound` representing the degree bound which we want for out bMST and setting it to 0 gives the output without any degree bound (i.e. tries to reduce the degree of the output as much as possible).
  - `Kruskals` - This contains the implementation of both the original `Kruskal's` algorithm and its modified version which takes in a degree bound and is a heuristic for the bMST problem.
  - `Prims` - This contains the implementation of both the original `Prim's` algorithm and its modified version which takes in a degree bound and is a heuristic for the bMST problem.
  - `test_script.sh` - This file is used to generate the results of weight and running for the three heuristics on the `omega/omega_weighted` dataset and output them in a format which is usable in markdown.
  - `main.cpp` - This is run the `test_script.sh` file to generate results for a single graph. 
- The **datasets** folder contains all the datatsets that were used to evaluate the code and generate results.
  - `alpha` - `alpha` is a dataset with weighted and unweighted random graphs. In each weighting category, there are 15 sparse to moderately dense graphs of size 300 nodes with 25 perturbations each.
  - `delta` - `delta` is a dataset with random Euclidean graphs. It has 35 Euclidean graphs of size varying from 300 to 1000 nodes with 15 perturbations each.
  - `epsilon` - This is a small dataset with 6 random graphs used for debugging purposes.
  - `omega` - `omega` is a dataset with weighted and unweighted random graphs. In each weighting category, there are 50 sparse graphs of size varying from 100 to 1000 nodes with varied densities and 15 perturbations each.
- The **Results.md** file contains the results of evaluation of the different algorithms on different datasets in tabular format.

## Running the Code
 
Simply running
```
bash test_script.sh
```
in the code folder creates the required outputs.
